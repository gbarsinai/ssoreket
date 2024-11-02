import os
import tkinter as tk
from tkinter import filedialog, scrolledtext

PROCESSED_FOLDERS_FILE = "processed_folders.txt"

def load_processed_folders():
    """Load the list of already processed folders from a file."""
    if os.path.exists(PROCESSED_FOLDERS_FILE):
        with open(PROCESSED_FOLDERS_FILE, "r" , encoding="utf-8") as file:
            return set(line.strip() for line in file)
    return set()

def save_processed_folder(folder_path):
    """Save a folder path to the processed folders file."""
    with open(PROCESSED_FOLDERS_FILE, "a" , encoding="utf-8") as file:
        file.write(folder_path + "\n")

def rename_files_in_folder(folder_path, label, processed_folders, processed_folders_list):
    for root, dirs, files in os.walk(folder_path):
        # Skip folders that were already processed
        if root in processed_folders:
            continue

        if files:
            # Update the label with the current folder being processed
            current_folder = os.path.basename(root)
            label.config(text=f"Processing folder: {current_folder}")
            label.update()

            parent_folder_name = os.path.basename(root)
            files = sorted(files, reverse=("אלבומי כיסים" in root))
            for index, filename in enumerate(files):
                file_extension = os.path.splitext(filename)[1]
                new_name = f"{parent_folder_name}_{index + 1}{file_extension}"
                os.rename(os.path.join(root, filename), os.path.join(root, new_name))
                print(f"Renamed {filename} to {new_name}")

            # Mark this folder as processed and add to list for summary
            save_processed_folder(root)
            processed_folders_list.append(root)

def show_summary_window(processed_folders_list):
    """Show a summary window with the list of processed folders."""
    summary_window = tk.Toplevel()
    summary_window.title("Summary of Processed Folders")

    # Label for summary
    summary_label = tk.Label(summary_window, text="Folders processed in this session:")
    summary_label.pack(pady=(10, 5))

    # Scrollable text widget to show the list of folders
    folder_list_text = scrolledtext.ScrolledText(summary_window, wrap=tk.WORD, width=50, height=15)
    folder_list_text.pack(padx=10, pady=(0, 10))
    folder_list_text.insert(tk.END, "\n".join(processed_folders_list))
    folder_list_text.config(state=tk.DISABLED)  # Make text read-only

    # OK button to close the summary window
    ok_button = tk.Button(summary_window, text="OK", command=summary_window.destroy)
    ok_button.pack(pady=(0, 10))

    # Keep the summary window open
    summary_window.grab_set()
    summary_window.wait_window()

def main():
    root = tk.Tk()
    root.withdraw()  # Hide the main window for file selection
    folder_path = filedialog.askdirectory(title="Select a Folder")
    
    if folder_path:
        # Load processed folders list
        processed_folders = load_processed_folders()
        processed_folders_list = []  # List to track folders processed in this run

        # Create a small window to show the current folder being processed
        progress_window = tk.Toplevel()
        progress_window.title("Renaming Progress")
        
        # Label to display the current folder
        label = tk.Label(progress_window, text="Starting...")
        label.pack(padx=20, pady=20)
        
        # Run the renaming function with folder updates
        rename_files_in_folder(folder_path, label, processed_folders, processed_folders_list)
        
        # Close the progress window when done
        progress_window.destroy()

        # Show summary window after processing
        show_summary_window(processed_folders_list)

if __name__ == "__main__":
    main()
