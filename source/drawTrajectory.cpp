#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>

#include "TCanvas.h"
#include "TGraph2D.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TText.h"

std::vector<std::string> split(std::string& input, char delimiter)
{
    std::istringstream stream(input);
    std::string field;
    std::vector<std::string> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

int main(int argc, char** argv) {

    std::string datapath = argv[1];
    std::ifstream datafile(datapath);
    std::string line;

    TCanvas *cvs = new TCanvas("cvs", "cvs", 800, 800);
    TGraph2D *tg_sun = new TGraph2D();
    TGraph2D *tg_h = new TGraph2D();
    TGraph2D *tg_e = new TGraph2D();
    TGraph2D *tg_r = new TGraph2D();

    std::vector<double> v_x_h, v_y_h, v_z_h;
    std::vector<double> v_x_e, v_y_e, v_z_e;
    std::vector<double> v_x_r, v_y_r, v_z_r;

    int N = 6;
    while (std::getline(datafile, line)) {
        std::vector<std::string> data = split(line, ',');
        if (!isdigit(data[0][0])) continue;
        std::string utc = data[0];
        std::vector<std::string> datetime = split(utc, '.');
        std::string date = datetime[0];
        std::string time = datetime[1];
        std::string lp  = data[1];
        double x_h   = std::stod(data[2]);
        double y_h   = std::stod(data[3]);
        double z_h   = std::stod(data[4]);
        double x_e   = std::stod(data[5]);
        double y_e   = std::stod(data[6]);
        double z_e   = std::stod(data[7]);
        double x_r   = std::stod(data[8]);
        double y_r   = std::stod(data[9]);
        double z_r   = std::stod(data[10]);
        // double rs    = std::stod(data[11]);
        // double re    = std::stod(data[12]);
        // double ra    = std::stod(data[13]);
        // double vs    = std::stod(data[14]);
        // double ve    = std::stod(data[15]);
        // double alpha = std::stod(data[16]);
        // double delta = std::stod(data[17]);
        // double dflt  = std::stod(data[18]);
        v_x_h.push_back(x_h);
        v_y_h.push_back(y_h);
        v_z_h.push_back(z_h);
        v_x_e.push_back(x_e);
        v_y_e.push_back(y_e);
        v_z_e.push_back(z_e);
        v_x_r.push_back(x_r);
        v_y_r.push_back(y_r);
        v_z_r.push_back(z_r);

        TGraph2D *tg_tr_h = new TGraph2D(v_x_h.size(), &v_x_h[0], &v_y_h[0], &v_z_h[0]);
        tg_tr_h->SetName("tg_tr_h");
        TGraph2D *tg_tr_e = new TGraph2D(v_x_e.size(), &v_x_e[0], &v_y_e[0], &v_z_e[0]);
        tg_tr_e->SetName("tg_tr_e");
        TGraph2D *tg_tr_r = new TGraph2D(v_x_r.size(), &v_x_r[0], &v_y_r[0], &v_z_r[0]);
        tg_tr_r->SetName("tg_tr_r");

        tg_sun->SetPoint(0, 0., 0., 0.);
        tg_h->SetPoint(0, x_h, y_h, z_h);
        tg_e->SetPoint(0, x_e, y_e, z_e);
        tg_r->SetPoint(0, x_r, y_r, z_r);

        tg_sun->SetMarkerStyle(4);
        tg_sun->SetMarkerSize(5);
        tg_e->SetMarkerSize(2);
        tg_h->SetMarkerStyle(41);
        tg_e->SetMarkerStyle(20);
        tg_r->SetMarkerStyle(20);
        tg_h->SetMarkerColor(2);
        tg_e->SetMarkerColor(3);
        tg_r->SetMarkerColor(4);
        tg_tr_h->SetMarkerColor(2);
        tg_tr_e->SetMarkerColor(3);
        tg_tr_r->SetMarkerColor(4);

        tg_sun->SetMaximum(1.5);
        tg_sun->SetMinimum(-1.5);
        tg_sun->GetXaxis()->SetLimits(-1.5, 1.5);
        tg_sun->GetYaxis()->SetLimits(-1.5, 1.5);
        tg_sun->SetTitle("");
        tg_sun->GetXaxis()->SetTitle("[AU]");
        tg_sun->GetXaxis()->SetTitleOffset(2.0);
        tg_sun->GetYaxis()->SetTitle("[AU]");
        tg_sun->GetYaxis()->SetTitleOffset(2.0);
        tg_sun->GetZaxis()->SetTitle("[AU]");
        tg_sun->GetZaxis()->SetTitleOffset(1.3);

        tg_sun->Draw("p");
        tg_h->Draw("p same");
        tg_e->Draw("p same");
        tg_r->Draw("p same");
        tg_tr_h->Draw("p same");
        tg_tr_e->Draw("p same");
        tg_tr_r->Draw("p same");

        TLegend *leg = new TLegend(0.05, 0.85, 0.3, 0.95);
        leg->SetFillStyle(0);
        leg->SetBorderSize(0);
        leg->AddEntry(tg_h, "Hayabusa", "p");
        leg->AddEntry(tg_e, "Earth", "p");
        leg->AddEntry(tg_r, "Ryugu", "p");
        leg->Draw();

        TText *text_date = new TText(0.4, 0.95, date.c_str());
        text_date->SetTextSize(0.04);
        text_date->SetTextFont(42);
        text_date->Draw();


        TText *text_time = new TText(0.4, 0.85, Form("day = %s", lp.c_str()));
        text_time->SetTextSize(0.04);
        text_time->SetTextFont(42);
        text_time->Draw();

        TText *text_sun = new TText(0, 0, "sun");
        text_sun->SetTextAlign(22);
        text_sun->SetTextFont(42);
        text_sun->SetTextSize(0.03);
        text_sun->Draw();

        std::string day = std::string(std::max(0, N-(int)lp.size()), '0') + lp;
        cvs->SaveAs(Form("./img/trajectory_day%s.png", day.c_str()));

        delete tg_tr_e;
        delete tg_tr_h;
        delete tg_tr_r;
    }

    return 0;
}