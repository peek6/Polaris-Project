# Tekken 8 Mesh Modding Tutorial

**Author:** peek

This tutorial walks you through the process of modding meshes in *Tekken 8*, including both mesh replacement and item prefab-based modding. The guide assumes familiarity with tools like Blender, Unreal Engine, and modding concepts. 

---

## Prerequisites

### Tools You'll Need
- [fmodel](https://fmodel.app/)  for exporting JSONs to locate MI paths/names, skeleton paths/names, etc.
- [grepWin](https://github.com/stefankueng/grepWin) for quick searching.
- Umodel (Tekken 8-specific version):  Download from [this NexusMods link](https://www.nexusmods.com/tekken8/mods/435?tab=files&file_id=1192). All credit to [Gildor](https://www.gildor.org/en/projects/umodel) for Umodel.
- Blender (recommended: v3.6)  
- Download the plugin [io_scene_gltf2_ue4.zip](https://github.com/KhronosGroup/glTF-Blender-IO) for importing/exporting GLTFs.
- Unreal Engine (custom version 5.2): [Custom UE 5.2 engine](https://drive.google.com/drive/folders/1TUmRc7qTq1xTUkGcWnPz6-2KuA4RTPOf)
- Custom Tekken 8 Project , mm_mi_tex branch:  [Polaris Project (mm_mi_tex branch)](https://github.com/peek6/Polaris-Project/tree/mm_mi_tex)


---

## Mesh Replacement Modding

### Step 1: Export Meshes
1. Open Umodel:
   - Set it to export as GLTF with **all weights per vertex** enabled.
   - Export the desired meshes (e.g., the mesh to replace or meshes to use as parts).

### Step 2: Set Up in Blender
1. Set "Unit Scale" to `0.01` in **Scene Properties**.
2. Import GLTFs for the original ("target") and new ("custom") meshes.
3. Rename MIs in the custom mesh to match the target mesh using JSON data exported via fmodel.
   - Ensure the custom mesh has at least as many MIs as the target mesh.  I generally recommend matching the MI names to the target JSON MI names exactly.  You can use [my script here](https://github.com/peek6/Json2DA/blob/b23198f47a2a57f9acc9727b2889918251ff5d25/change_blender_material_names.py) to automatically import the target MI names onto your Blender mesh if you modify the mesh_json_path to point to the target mesh's JSON file extracted using Fmodel. 
4. Align the custom mesh to the target mesh (e.g., using [this video guide](https://www.youtube.com/watch?v=XZ748t5KQv8) from 5:37–14:56).
5. Rename the target skeleton to `Armature` and parent the custom mesh to it.
6. Delete all weights from the custom mesh, then transfer weights from the target mesh (refer to [this video](https://www.youtube.com/watch?v=bR_Vke__voU)).
7. Export the updated mesh as FBX using [this plugin](https://github.com/matyalatte/blender3d_import_psk_psa/releases).

### Step 3: Import to Unreal Engine
1. Import the FBX into Unreal Engine so that it has the exact same folder path and name as the original game's target mesh you want to replace:
   - Match skeleton and MI paths/names from the target mesh's JSON file.
   - Include only the mesh in the chunk, excluding skeletons or MIs.
   - Package the mod.

### Step 4: Additional Steps for PRP Targets
If the target mesh also has PRP:
1. Import the target PRP GLTF into the same Blender project/window as above.
2. Rename the skeleton from above to anything other than `Armature` (for example, rename it as `Armature MSL`), and then rename the PRP skeleton you just imported to `Armature`.
3. Parent the EXACT SAME MSL mesh you exported above to the PRP skeleton.
4. Delete the MSL mesh's weights, transfer weights from the imported PRP mesh to your MSL mesh (referring again to [this video](https://www.youtube.com/watch?v=bR_Vke__voU)), and export your new custom PRP mesh as FBX using [this plugin](https://github.com/matyalatte/blender3d_import_psk_psa/releases).
5. Import your PRP mesh into Unreal Engine (as well as your MSL mesh if you didn't already import it), linking each to the respective skeleton and MI paths from JSON.
6. Package the mod.

### Final Step: Install the Mod
1. Place your packaged mod into the `LogicMods` directory and ensure all filenames end with `_P`. You can automate this with my [Python script](https://github.com/peek6/Json2DA/blob/tekken8/ue_mod_installer.py) provided in the custom project.

---

## Item Prefab-Based Modding

### Overview
Tekken 8 has a really cool system where every slot has an asset called an Item Prefab (IP) which points to three other assets:  a Base Character Item (BCI), a Customize Item (CI), and a Base Item (BI).  The BI points to the mesh.

The following tutorial takes advantage of this system to allow you to put your own custom mods into any slot, without overwriting any of the game's existing assets other than IPs. 


### Step-by-Step Guide
1. Export JSONs with [fmodel](https://fmodel.app/).
2. Clone the custom Polaris UE Project ([mm_mi_tex branch](https://github.com/peek6/Polaris-Project/tree/mm_mi_tex)).
3. Grab the UE 5.2 custom engine from [Custom UE 5.2 engine](https://drive.google.com/drive/folders/1TUmRc7qTq1xTUkGcWnPz6-2KuA4RTPOf) and set project/editor settings as described in [this guide](https://modding.wiki/en/hogwartslegacy/developers/getting-started).  You can now import most types of assets into the game as follows:
     - create the asset in UE by right-clicking within your desired folder and picking the asset type you want from the "Polaris" Menu.
     - right-click the asset you just created, select "scripted asset actions" and select "Import JSON" then browse to the corresponding JSON you extracted using [fmodel](https://fmodel.app/)
4. Organize custom assets:
   - Place custom meshes, textures, and MIs in a dedicated folder.
5. Create assets:
   - **BI:** Points to your custom mesh.  What I'll typically do is import an existing BI for a similar outfit and then modify it to point to my custom mesh.
   - **CI:** Defines coloring slots for MIs.  Again I usually start by importing one from the original game which has the coloring slots for its MIs set up as I want, and modify it as needed to point to any new MIs I've made.
   - **BCI:** Just create a blank one.
6. Overwrite the original IP for the desired slot:
   - Modify it to point to your custom BI, CI, and BCI.
7. Package the mod:
   - Include the IP and all custom assets in your chunk.  You can easily do this by creating a primary asset label in your mod directory, checking the box to label all assets in your directory, and adding your IP as an explicit asset.  Then just package in UE as usual. 
   - Place your packaged mod into the `LogicMods` directory and ensure all filenames end with `_P`. You can automate this with my [Python script](https://github.com/peek6/Json2DA/blob/tekken8/ue_mod_installer.py) provided in the custom project.

Note that the only original T8 asset you are modifying with this approach is the IP. Everything else can (and should) be under your own custom directory for this mod.

As a bonus, if you followed the above approach, I included a Python script in Content/Python/outfit_selector.py which will allow you to let people choose which custom part they want to replace. Follow the instructions I gave in the script's comments detailing how it should be setup and used.

---

Enjoy modding *Tekken 8*!
