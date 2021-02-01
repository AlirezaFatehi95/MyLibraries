"""windows batch file renamer :)"""

import os

FOLDER_PATH = "line_images"
def renamer():
    """this function obviously is renaming the FOLDER_PATH"""
    i = 0
    for file_name in os.listdir(FOLDER_PATH):
        src = FOLDER_PATH + "\\" + file_name
        dst = FOLDER_PATH + "\\" + "scene" + str(i) + ".jpg"
        i += 1
        os.rename(src, dst)

if __name__ == "__main__":
    renamer()
