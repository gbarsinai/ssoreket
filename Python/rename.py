import os
import tkinter as tk
from tkinter import filedialog

def rename_files_in_folder(folder_path):
    for root, dirs, files in os.walk(folder_path):
        if files:
            parent_folder_name = os.path.basename(root)
            if "אלבומי כיסים" in root:
                files = sorted(files, reverse=True)
            else:
                files = sorted(files)
            for index, filename in enumerate(files):
                file_extension = os.path.splitext(filename)[1]
                new_name = f"{parent_folder_name}_{index + 1}{file_extension}"
                os.rename(os.path.join(root, filename), os.path.join(root, new_name))
                print(f"Renamed {filename} to {new_name}")

def main():
    root = tk.Tk()
    root.withdraw()  # Hide the root window
    folder_path = filedialog.askdirectory(title="Select a Folder")
    if folder_path:
        rename_files_in_folder(folder_path)

if __name__ == "__main__":
    main()