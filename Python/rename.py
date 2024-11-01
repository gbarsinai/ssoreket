import os

def rename_files_in_subfolders(root_folder):
    # Get the parent directory name
    parent_dir_name = os.path.basename(os.path.normpath(root_folder))

    #if the renaming process has already started exit the function
    if os.path.exists(os.path.join(root_folder, "renaming_process.txt")):
        print("The renaming process has already started")
        return
    
    # place a file to indicate the renaming process in the root folder
    with open(os.path.join(root_folder, "renaming_process.txt"), "w") as f:
        f.write("Renaming process started")

    # Walk through the directory
    for subdir, _, files in os.walk(root_folder):
        if subdir == root_folder:
            continue  # Skip the root folder itself
        
        # Check if the subfolder is "אלבומי כיסים"
        if os.path.basename(subdir) == "אלבומי כיסים":
            files = sorted(files, reverse=True)
        
        for index, file in enumerate(files):
            file_path = os.path.join(subdir, file)
            file_extension = os.path.splitext(file)[1]
            new_file_name = f"{parent_dir_name}_{index}{file_extension}"
            new_file_path = os.path.join(subdir, new_file_name)
            
            # Check if the file is already renamed
            if file == new_file_name:
                continue
            
            os.rename(file_path, new_file_path)
            print(f"Renamed: {file_path} to {new_file_path}")

if __name__ == "__main__":
    folder_path = input("Enter the folder path: ")
    rename_files_in_subfolders(folder_path)