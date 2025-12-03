#!/usr/bin/env python3
import os

# Root folder to start scanning
ROOT_DIR = os.getcwd()  # Current working directory

# Default README content template
README_TEMPLATE = """# {dir_name}

This folder is part of the repository and contains source code or resources related to `{dir_name}`.

---

## Contents

- Add description of files here
- Add purpose of this folder

"""

# Extensions to consider as existing README
README_NAMES = ["README.md", "README.ld"]

def has_readme(folder):
    """Check if folder contains any README file"""
    for name in README_NAMES:
        if os.path.isfile(os.path.join(folder, name)):
            return True
    return False

def create_readme(folder):
    """Create README.md in the folder with default content"""
    dir_name = os.path.basename(folder)
    readme_path = os.path.join(folder, "README.md")
    content = README_TEMPLATE.format(dir_name=dir_name)
    with open(readme_path, "w") as f:
        f.write(content)
    print(f"Created README.md in {folder}")

def main():
    for dirpath, dirnames, filenames in os.walk(ROOT_DIR):
        # Skip hidden directories
        if os.path.basename(dirpath).startswith('.'):
            continue
        if not has_readme(dirpath):
            create_readme(dirpath)

if __name__ == "__main__":
    main()

