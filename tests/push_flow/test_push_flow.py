from PIL import Image
import time
import subprocess
import numpy as np


def test():
    fps = 5
    rtmp_link = "rtmp://live-push.bilivideo.com/live-bvc/?streamname=live_12070196_2094942&key=2482a0019cb48b7cd4d7eb97bfe1191f&schedule=rtmp&pflag=1"
    # rtmp_link = "test_push.flv"
    commands = f'ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s 2560x1440 -r {fps} -i - -c:v libx264 -pix_fmt yuv420p -preset fast -acodec aac -b:a 192k -f flv {rtmp_link}'.split(
        ' ')
    pipe = subprocess.Popen(commands, stdin=subprocess.PIPE)
    # with open("../../resource/test.png", "rb") as f:
    #   test_data = f.read()
    im = Image.open("../../resource/test.png")
    n = np.asarray(im)
    print(f"shape = {n.shape}")
    test_data = n.tobytes()
    while True:
        if (pipe.stdin.writable):
            pipe.stdin.write(test_data)
            pipe.stdin.flush()
        else:
            time.sleep(0.01)


if __name__ == '__main__':
    test()
