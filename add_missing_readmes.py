#!/usr/bin/env python3
import os

# Template for new README.md
TEMPLATE = """# {dirname}

This directory `{dirname}` contains source code and/or resources for the project.  
Add more description about this module here.
"""

# Walk through the current directory
for root, dirs, files in os.walk("."):
    # Skip hidden directories
    dirs[:] = [d for d in dirs if not d.startswith(".")]

    # Rename README.ld to README.md if exists
    if "README.ld" in files:
        old_path = os.path.join(root, "README.ld")
        new_path = os.path.join(root, "README.md")
        os.rename(old_path, new_path)
        print(f"Renamed: {old_path} -> {new_path}")

    # Check if README.md exists
    if "README.md" not in files:
        readme_path = os.path.join(root, "README.md")
        dirname = os.path.basename(os.path.abspath(root))
        with open(readme_path, "w") as f:
            f.write(TEMPLATE.format(dirname=dirname))
        print(f"Created README.md in: {root}")

