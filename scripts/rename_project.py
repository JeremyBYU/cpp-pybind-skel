import argparse
from pathlib import Path
import shutil
import logging
import sys

logging.basicConfig(level=logging.INFO)

CPPLIB_FULL_NAME = "CPPLib"
CPPLIB_FULL_NAME_CAPS = "CPPLIB"
CPPLIB_SHORT = "CPPL"
CPPLIB_LOWERCASE = "cpplib"

REPLACE_LIST = [CPPLIB_FULL_NAME, CPPLIB_FULL_NAME_CAPS,
                CPPLIB_SHORT, CPPLIB_LOWERCASE]

INCLUDE_FOLDERS = ["bench", "src_docs", "examples", "include", "src", "tests"]
EXCLUDE_FOLDERS = ["_out", "cpp_api", "python_api"]


def parse_args():
    parser = argparse.ArgumentParser("Renames Project Files")
    parser.add_argument("--libname",
                        default=CPPLIB_FULL_NAME,
                        help="Full name of Library (e.g., CPPLib). Should have uppercase.")
    parser.add_argument("--libname_short",
                        default=CPPLIB_SHORT,
                        help="Short acronym of Library (e.g., CPPL). Should be all uppercase.")
    parser.add_argument("--libname_python",
                        default=CPPLIB_LOWERCASE,
                        help="Full name of Python Extension Library (e.g., cpplib). Should be lowercase.")
    args = parser.parse_args()

    return args


def replace_string_list(name: str, replace_list=REPLACE_LIST,
                        to_list=[]):
    assert(len(replace_list) == len(to_list))

    for (from_str, to_str) in zip(replace_list, to_list):
        if from_str in name:
            new_name = name.replace(from_str, to_str)
            return True, new_name
    return False, ""


def rename_file_or_folder(path_file_or_folder, new_names):
    stem = str(path_file_or_folder.name)
    need_rename, new_name = replace_string_list(stem, to_list=new_names)
    if need_rename:
        new_directory_or_file = path_file_or_folder.parent / new_name
        logging.info("Need rename - %s -> %s",
                     path_file_or_folder, new_directory_or_file)
        path_file_or_folder.rename(new_directory_or_file)


def replace_strings_in_file(fpath, replace_list=REPLACE_LIST,
                    to_list=[]):
    try:
        with open(fpath, 'rt') as f:
            new_file_text = f.read()
            for (from_str, to_str) in zip(replace_list, to_list):
                new_file_text = new_file_text.replace(from_str, to_str)

        with open(fpath, "w") as f:
            f.write(new_file_text)
    except Exception:
        logging.info("Can't inspect file for string replacement - %s", fpath)


def traverse_folder(directory, **kwargs):
    new_names = [kwargs['libname'], kwargs['libname'].upper(),
                 kwargs['libname_short'], kwargs['libname_python']]
    logging.debug("Traversing %s", directory)
    for path_file_or_folder in directory.iterdir():
        # Folder
        if path_file_or_folder.is_dir():
            if str(path_file_or_folder.stem) not in EXCLUDE_FOLDERS:
                traverse_folder(path_file_or_folder, **kwargs)
        # File
        else:
            # replace text here
            logging.info("Inspecting file %s", path_file_or_folder)
            replace_strings_in_file(path_file_or_folder, to_list=new_names)
            # rename file here
            rename_file_or_folder(path_file_or_folder, new_names)

    # Rename folder if needed
    rename_file_or_folder(directory, new_names)


def rename_files(base, libname, libname_short, libname_python):
    for include_folder in INCLUDE_FOLDERS:
        folder = base / include_folder
        traverse_folder(folder, libname=libname,
                        libname_short=libname_short, libname_python=libname_python)


def ignore_folders(directory, contents):
    filtered = [content for content in contents if content in [
        'build', 'cmake-build', '.git', 'cpp_api', 'python_api', 'dist', 'wheelhouse']]
    return filtered


def main():
    args = parse_args()

    base = Path(__file__).parent.parent
    new_base = (base / "../" / args.libname).resolve()

    if (new_base.exists()):
        logging.error("Please remove folder %s before proceeding. I won't do it for safety reasons.", new_base)
        sys.exit(1)
    
    logging.info("Copying skeleton to new directory")
    destination = shutil.copytree(base, new_base, ignore=ignore_folders)

    logging.info("Renaming files, Replacing Text")
    new_names = [args.libname, args.libname.upper(),
                 args.libname_short, args.libname_python]

    rename_files(new_base, args.libname,
                 args.libname_short, args.libname_python)

    logging.info("Renaming text in top level files")
    top_file = new_base / "CMakeLists.txt"
    replace_strings_in_file(top_file, to_list=new_names)
    top_file = new_base / "setup.py"
    replace_strings_in_file(top_file, to_list=new_names)

    logging.info("Setting version to 0.0.1")
    with open(Path(new_base) / 'src/version.txt', 'w') as f:
        f.write("MAJOR {}\nMINOR {}\nPATCH {}".format(0, 0, 1))



if __name__ == "__main__":
    main()
