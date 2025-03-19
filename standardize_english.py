#!/usr/bin/env python3
# filepath: standardize_english.py
import os
import re
from pathlib import Path
import shutil
import argparse

# Translation mappings
CLASS_TRANSLATIONS = {
    'Joueur': 'Player',
    'Paiement': 'Payment',
    'Terrain': 'Court',
    'Place': 'Seat',
    'Partie': 'Game'
}

MANAGER_TRANSLATIONS = {
    'GestionJoueurs': 'PlayerManager',
    'GestionPlaces': 'SeatManager',
    'GestionTerrains': 'CourtManager',
    'GestionPaiements': 'PaymentManager',
    'GestionTickets': 'TicketManager',
    'GestionReservations': 'ReservationManager',
    'GestionScore': 'ScoreManager',
    'GestionMatch': 'MatchManager',
    'GestionClients': 'ClientManager',
    'GestionSeats': 'SeatManager',
    'GestionScores': 'ScoreManager',
    'GestionParties': 'GameManager',
    'gestionJoueurs': 'playerManager',
    'gestionPlaces': 'seatManager',
    'gestionTerrains': 'courtManager',
    'gestionPaiements': 'paymentManager',
    'gestionTickets': 'ticketManager',
    'gestionReservations': 'reservationManager'
}

METHOD_TRANSLATIONS = {
    r'\bajouter(\w+)\b': r'add\1',
    r'\bsupprimer(\w+)\b': r'remove\1',
    r'\bmodifier(\w+)\b': r'update\1',
    r'\bcreer(\w+)\b': r'create\1',
    r'\bgetPaiements\b': r'getPayments',
    r'\bgetJoueurs\b': r'getPlayers',
    r'\bgetTerrains\b': r'getCourts',
    r'\bgetPlaces\b': r'getSeats',
    r'\bgetNom\b': r'getName',
    r'\bgetJoueur1\b': r'getPlayer1',
    r'\bgetJoueur2\b': r'getPlayer2',
    r'\bPlaceId\b': r'SeatId',
    r'\bplaceId\b': r'seatId',
    r'\bPlanificationParties\b': r'TournamentScheduler',
    r'\bcreatePartieFinale\b': r'createFinalMatch',
    r'\bcreateParties16emes\b': r'createRoundOf16',
    r'\bcreateTournoi\b': r'createTournament'
}

GETTER_METHOD_TRANSLATIONS = {
    r'getNom': r'getName',
    r'getPlaceId': r'getSeatId',
    r'getPlaceById': r'getSeatById',
    r'getTerrainById': r'getCourtById'
}

VARIABLE_TRANSLATIONS = {
    r'\bnom\b': r'name',
    r'\bmontant\b': r'amount',
    r'\bmodePaiement\b': r'paymentMode',
    r'\bjoueur1\b': r'player1',
    r'\bjoueur2\b': r'player2',
    r'\bplacesModel\b': r'seatsModel',
    r'\bterrainsModel\b': r'courtsModel',
    r'\bpaiementsModel\b': r'paymentsModel',
    r'\bplacesTableView\b': r'seatsTableView',
    r'\bterrainsTableView\b': r'courtsTableView',
    r'\bpaiementsTableView\b': r'paymentsTableView'
}

# Files/paths to exclude
EXCLUDE_PATTERNS = [
    r'.*CMakeCache\.txt$',
    r'.*cmake_install\.cmake$',
    r'.*\.qm$',
    r'.*\.vcxproj$',
    r'.*\.vcxproj\.filters$',
    r'.*\.sln$',
    r'build/.*'
]

# UI element ID translations - for .ui files
UI_ELEMENT_TRANSLATIONS = {
    r'placesTableView': r'seatsTableView',
    r'terrainsTableView': r'courtsTableView',
    r'placeComboBox': r'seatComboBox',
    r'terrainComboBox': r'courtComboBox',
    r'placeLineEdit': r'seatLineEdit',
    r'terrainLineEdit': r'courtLineEdit',
    r'placeLabel': r'seatLabel',
    r'terrainLabel': r'courtLabel',
    r'placesLabel': r'seatsLabel',
    r'terrainsLabel': r'courtsLabel',
    r'addPlaceButton': r'addSeatButton',
    r'deletePlaceButton': r'deleteSeatButton',
    r'updatePlaceButton': r'updateSeatButton',
    r'addTerrainButton': r'addCourtButton',
    r'deleteTerrainButton': r'deleteCourtButton',
    r'updateTerrainButton': r'updateCourtButton',
}

def should_process_file(file_path):
    """Check if we should process this file based on exclusion patterns"""
    for pattern in EXCLUDE_PATTERNS:
        if re.match(pattern, file_path):
            return False
    return True

def process_file(file_path, dry_run=False):
    """Process a single file, applying translations."""
    if not should_process_file(file_path):
        print(f"Skipping {file_path}")
        return

    print(f"Processing {file_path}")
    
    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as file:
            content = file.read()
        
        original_content = content
        
        # For UI files, process UI element IDs
        if file_path.endswith('.ui'):
            for french, english in UI_ELEMENT_TRANSLATIONS.items():
                content = re.sub(french, english, content)
        
        # Handle literal filenames in includes but keep the actual filename as is
        # This is for when the file exists and can't be renamed (3rd party, generated, etc.)
        pattern = r'#include\s+[<"]([^<">]*?)(Joueur|Paiement|Terrain|Place|Gestion\w+)\.h[>"]'
        
        def replace_include_keep_filename(match):
            path, class_name = match.groups()
            
            # If the class name needs to be translated
            if class_name in CLASS_TRANSLATIONS:
                english_class = CLASS_TRANSLATIONS[class_name]
                # Keep the original filename but change the class reference
                return f'#include "{path}{class_name}.h"  // TODO: Update to {english_class}.h when file is renamed'
            
            # For Gestion classes
            for french, english in MANAGER_TRANSLATIONS.items():
                if class_name == french:
                    # Keep the original filename but change the class reference
                    return f'#include "{path}{class_name}.h"  // TODO: Update to {english}.h when file is renamed'
            
            return match.group(0)
        
        content = re.sub(pattern, replace_include_keep_filename, content)
        
        # Replace class names
        for french, english in CLASS_TRANSLATIONS.items():
            content = re.sub(r'\b' + french + r'\b', english, content)
        
        # Replace manager class names
        for french, english in MANAGER_TRANSLATIONS.items():
            content = re.sub(r'\b' + french + r'\b', english, content)
        
        # Replace method names
        for pattern, replacement in METHOD_TRANSLATIONS.items():
            content = re.sub(pattern, replacement, content)
        
        # Replace getter methods
        for pattern, replacement in GETTER_METHOD_TRANSLATIONS.items():
            content = re.sub(pattern, replacement, content)
        
        # Replace variable names
        for pattern, replacement in VARIABLE_TRANSLATIONS.items():
            content = re.sub(pattern, replacement, content)
            
        # Handle special case for string references to files in code
        # This replaces hardcoded UI file references like "placesui.ui" -> "seatsui.ui"
        # but only in string literals
        for french, english in {
            "joueur": "player", 
            "terrain": "court", 
            "place": "seat", 
            "paiement": "payment"
        }.items():
            content = re.sub(r'"([^"]*?)' + french + r'([^"]*?)"', r'"\1' + english + r'\2"', content)
            content = re.sub(r"'([^']*?)" + french + r"([^']*?)'", r"'\1" + english + r"\2'", content)
        
        # Only write if content changed and not in dry run mode
        if content != original_content and not dry_run:
            with open(file_path, 'w', encoding='utf-8') as file:
                file.write(content)
                print(f"  Updated {file_path}")
        elif content != original_content:
            print(f"  Would update {file_path}")
    
    except Exception as e:
        print(f"  Error processing {file_path}: {str(e)}")

def rename_files(base_path, dry_run=False):
    """Rename files according to translation rules."""
    renamed_files = []
    
    # Map of French filename patterns to English equivalents
    filename_map = {}
    
    # Add class files to map
    for french, english in CLASS_TRANSLATIONS.items():
        filename_map[f"{french}.h"] = f"{english}.h"
        filename_map[f"{french}.cpp"] = f"{english}.cpp"
    
    # Add manager files to map
    for french, english in MANAGER_TRANSLATIONS.items():
        if french.startswith('Gestion'):  # Only process class names, not variable names
            filename_map[f"{french}.h"] = f"{english}.h"
            filename_map[f"{french}.cpp"] = f"{english}.cpp"
    
    # Add UI files to map
    for french, english in {
        "placesui": "seatsui",
        "terrainsui": "courtsui",
        "paiementsui": "paymentsui"
    }.items():
        filename_map[f"{french}.ui"] = f"{english}.ui"
        filename_map[f"{french}.h"] = f"{english}.h"
        filename_map[f"{french}.cpp"] = f"{english}.cpp"
    
    # Special case for PlanificationParties
    filename_map["PlanificationParties.h"] = "TournamentScheduler.h"
    filename_map["PlanificationParties.cpp"] = "TournamentScheduler.cpp"
    
    for root, dirs, files in os.walk(base_path):
        # Skip the build directory
        if "build" in root.split(os.sep):
            continue
            
        for file in files:
            # Skip files we shouldn't process
            if not should_process_file(os.path.join(root, file)):
                continue
                
            new_file = file
            
            # Check if file matches any pattern to be renamed
            for old_pattern, new_pattern in filename_map.items():
                if file.endswith(old_pattern):
                    prefix = file[:-len(old_pattern)]
                    new_file = prefix + new_pattern
                    break
            
            if new_file != file:
                old_path = os.path.join(root, file)
                new_path = os.path.join(root, new_file)
                
                if os.path.exists(new_path):
                    print(f"  Warning: Cannot rename {old_path} to {new_path} - target file already exists")
                    continue
                
                print(f"Renaming {old_path} to {new_path}")
                renamed_files.append((old_path, new_path))
                
                if not dry_run:
                    try:
                        os.rename(old_path, new_path)
                    except Exception as e:
                        print(f"  Error renaming {old_path}: {str(e)}")
    
    return renamed_files

def update_cmake(base_path, renamed_files, dry_run=False):
    """Update CMakeLists.txt files to reflect renamed files"""
    for root, dirs, files in os.walk(base_path):
        for file in files:
            if file == "CMakeLists.txt":
                file_path = os.path.join(root, file)
                print(f"Checking CMake file: {file_path}")
                
                try:
                    with open(file_path, 'r', encoding='utf-8') as f:
                        content = f.read()
                    
                    original = content
                    
                    # Replace all renamed files in the CMake content
                    for old_path, new_path in renamed_files:
                        # Get the filename only for CMake replacement
                        old_file = os.path.basename(old_path)
                        new_file = os.path.basename(new_path)
                        content = content.replace(old_file, new_file)
                    
                    # Also update class names, manager names in filenames
                    for french, english in CLASS_TRANSLATIONS.items():
                        content = re.sub(r'\b' + french + r'\.h\b', english + '.h', content)
                        content = re.sub(r'\b' + french + r'\.cpp\b', english + '.cpp', content)
                    
                    for french, english in MANAGER_TRANSLATIONS.items():
                        if french.startswith('Gestion'):  # Only process class names
                            content = re.sub(r'\b' + french + r'\.h\b', english + '.h', content)
                            content = re.sub(r'\b' + french + r'\.cpp\b', english + '.cpp', content)
                    
                    # Special case for PlanificationParties
                    content = content.replace("PlanificationParties.h", "TournamentScheduler.h")
                    content = content.replace("PlanificationParties.cpp", "TournamentScheduler.cpp")
                    
                    if content != original and not dry_run:
                        with open(file_path, 'w', encoding='utf-8') as f:
                            f.write(content)
                        print(f"  Updated {file_path}")
                    elif content != original:
                        print(f"  Would update {file_path}")
                except Exception as e:
                    print(f"  Error updating CMake file {file_path}: {str(e)}")

def update_project_files(base_path, renamed_files, dry_run=False):
    """Update project files (.vcxproj, etc.) to reflect renamed files"""
    project_extensions = ['.vcxproj', '.sln', '.vcxproj.filters']
    
    for root, dirs, files in os.walk(base_path):
        for file in files:
            if any(file.endswith(ext) for ext in project_extensions):
                file_path = os.path.join(root, file)
                print(f"Checking project file: {file_path}")
                
                try:
                    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    
                    original = content
                    
                    # Replace all renamed files in the project files
                    for old_path, new_path in renamed_files:
                        # Get the filename only for replacement
                        old_file = os.path.basename(old_path)
                        new_file = os.path.basename(new_path)
                        content = content.replace(old_file, new_file)
                    
                    if content != original and not dry_run:
                        with open(file_path, 'w', encoding='utf-8') as f:
                            f.write(content)
                        print(f"  Updated {file_path}")
                    elif content != original:
                        print(f"  Would update {file_path}")
                except Exception as e:
                    print(f"  Error updating project file {file_path}: {str(e)}")

def create_backup(base_path, dry_run=False):
    """Create a backup of the codebase before starting"""
    backup_dir = f"{base_path}_backup_{Path().resolve().name}"
    print(f"Creating backup in {backup_dir}...")
    
    if os.path.exists(backup_dir):
        print(f"Backup directory {backup_dir} already exists. Please remove it first.")
        return False
    
    if not dry_run:
        try:
            shutil.copytree(base_path, backup_dir)
            print(f"Backup created successfully in {backup_dir}")
            return True
        except Exception as e:
            print(f"Failed to create backup: {str(e)}")
            return False
    else:
        print(f"Would create backup in {backup_dir}")
        return True

def main():
    parser = argparse.ArgumentParser(description='Standardize English in codebase')
    parser.add_argument('--dry-run', action='store_true', help='Show what would be done without making changes')
    parser.add_argument('--no-backup', action='store_true', help='Skip creating a backup')
    parser.add_argument('--skip-rename', action='store_true', help='Skip renaming files')
    parser.add_argument('--path', default="app", help='Base path to start from (default: app)')
    args = parser.parse_args()
    
    base_path = args.path
    
    # Create backup unless --no-backup is specified
    if not args.no_backup and not args.dry_run:
        if not create_backup(base_path, args.dry_run):
            return
    
    # First, process file content
    for ext in ['.cpp', '.h', '.ui', '.qrc', '.txt']:
        for file_path in Path(base_path).rglob(f'*{ext}'):
            if should_process_file(str(file_path)):
                process_file(str(file_path), args.dry_run)
    
    # Then rename files if not skipped
    if not args.skip_rename:
        renamed_files = rename_files(base_path, args.dry_run)
        
        # Update CMakeLists.txt with the new filenames
        update_cmake(base_path, renamed_files, args.dry_run)
        
        # Update project files
        update_project_files(base_path, renamed_files, args.dry_run)
    else:
        print("Skipping file renaming as requested.")
        renamed_files = []
    
    print("\nEnglish standardization " + ("would be " if args.dry_run else "") + "complete!")
    
    if not args.dry_run:
        print("\nCODEBASE STANDARDIZATION SUMMARY:")
        print("--------------------------------")
        print(f"Files processed: {len(list(Path(base_path).rglob('*.[ch]'))) + len(list(Path(base_path).rglob('*.cpp')))}")
        print(f"Files renamed: {len(renamed_files)}")
        print("\nNOTE: You may need to manually update project files and rebuild your project.")
        print("Check for any build errors after running this script.")
        print("\nRemaining tasks:")
        print("1. Update any hardcoded string literals that reference old filenames")
        print("2. Fix commented-out include paths marked with '// TODO: Update' comments")
        print("3. Fix any remaining French-to-English inconsistencies in your code")
        print("4. Test the application thoroughly to ensure functionality")

if __name__ == "__main__":
    main()