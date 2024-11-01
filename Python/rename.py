import os

def rename_files_in_subfolders(root_folder):
    # Get the parent directory name
    parent_dir_name = os.path.basename(os.path.normpath(root_folder))
    
    # Walk through the directory
    for subdir, _, files in os.walk(root_folder):
        if subdir == root_folder:
            continue  # Skip the root folder itself
        
        for index, file in enumerate(files):
            file_path = os.path.join(subdir, file)
            file_extension = os.path.splitext(file)[1]
            new_file_name = f"{parent_dir_name}_{index}{file_extension}"
            new_file_path = os.path.join(subdir, new_file_name)
            
            os.rename(file_path, new_file_path)
            print(f"Renamed: {file_path} to {new_file_path}")

if __name__ == "__main__":
    folder_path = input("Enter the folder path: ")
    rename_files_in_subfolders(folder_path)