from PIL import Image
import os

def convert_to_gif(input_dir, output_file, duration=100, loop=0, strip_duration=1):
    """
    Convert PNG files in the specified directory to a GIF.

    Parameters:
    - input_dir (str): Path to the directory containing PNG files.
    - output_file (str): Path to the output GIF file.
    - duration (int): Display duration for each frame in milliseconds.
    - loop (int): Number of loops (0 for infinite loop).
    """
    # Get a list of all PNG files in the input directory
    files = sorted([f for f in os.listdir(input_dir) if f.lower().endswith('.png')])

    if not files:
        print("No PNG files found in the specified directory.")
        return
    
    # Create a list to store the image frames
    frames = []

    # Open each PNG file and append it to the frames list
    for count, file in enumerate(files):
        png_path = os.path.join(input_dir, file)
        img = Image.open(png_path)
        if count % strip_duration == 0:
            frames.append(img)

    # Save the frames as a GIF
    frames[0].save(
        output_file,
        save_all=True,
        append_images=frames[1:],
        duration=duration,
        loop=loop
    )

    print(f"GIF saved to {output_file}")

# Example usage:
input_directory = '/home/user/personal/sandbox/hayabusa2_trajectry/data/img'
output_gif_file = '/home/user/personal/sandbox/hayabusa2_trajectry/data/trajectory.gif'
frame_duration = 10  # milliseconds
loop_count = 0  # 0 for infinite loop
strip_duration = 3

convert_to_gif(input_directory, output_gif_file, duration=frame_duration, loop=loop_count, strip_duration=strip_duration)