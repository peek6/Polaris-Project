# Tekken 8 Mesh Modding Tutorial

**Author:** peek

This tutorial walks you through the process of modding meshes in *Tekken 8*, including both mesh replacement and ItemPrefab-based modding. The guide assumes familiarity with tools like Blender, Unreal Engine, and modding concepts. 

---

## Prerequisites

### Tools You'll Need
- [fmodel](https://fmodel.app/)  for exporting JSON files which you can use for reference or for importing custom Tekken 8 datatypes into Unreal Engine (UE)
- [grepWin](https://github.com/stefankueng/grepWin) for quick searching.
- [Umodel (Tekken 8-specific version)](https://www.nexusmods.com/tekken8/mods/435?tab=files&file_id=1192) for exporting meshes as gltf with all weights.  Note that fmodel does not support exporting meshes with all weights, which will lead to neck gaps in-game, so always use umodel for exporting Tekken 8 meshes. Credit to [Gildor](https://www.gildor.org/en/projects/umodel) for Umodel.
- Blender (recommended version 3.6 LTS) from Microsoft Store. 
- [gltf import plugin for UE](https://cdn.discordapp.com/attachments/1135985731639181392/1203754525119488010/io_scene_gltf2_ue4.zip?ex=6738d6c3&is=67378543&hm=ff256b4188eb7ceb2f4b25ef501f5bb79264f7841c0fbe7eb58adcb37036b88b&) for importing/exporting GLTFs.
- [Matya FBX export plugin](https://github.com/matyalatte/blender3d_import_psk_psa/releases) for exporting your modded meshes from Blender so that they can be correctly imported into UE.
- [Custom UE 5.2 engine for Tekken 8](https://drive.google.com/drive/folders/1TUmRc7qTq1xTUkGcWnPz6-2KuA4RTPOf) is the custom unreal engine version required for packaging Tekken 8 mods
- [Custom Tekken 8 Project , mm_mi_tex branch](https://github.com/peek6/Polaris-Project/tree/mm_mi_tex) is the custom project which is already set up with all the Tekken 8 custom datatypes.  Use the mm_mi_tex branch to have all MIs already set up for you, pointing to dummy master materials and dummy textures.


---

## Mesh Replacement Modding

### Step 1: Export Meshes using Umodel and JSON files via Fmodel
1. Open Umodel:
   - Set the UE version to 5.2.
   - Set umodel to export as GLTF with **export all weights (gltf only)** enabled.
   - Export the desired meshes (e.g., the target mesh to replace and any meshes which you want to use in your mods).
3. Open [fmodel](https://fmodel.app/), go to the top-level character folder, right-click, and export all JSONs. They shouldn't take up a ton of space, and they are useful for getting MI paths/names, skeleton paths/names, etc. If you do this, you can then easily find any info you need using [grepWin](https://github.com/stefankueng/grepWin).

### Step 2: Create your custom modded mesh in Blender
1. Set "Unit Scale" to `0.01` in **Scene Properties**.
2. Import GLTFs for the original ("target") and new ("custom") meshes using [io_scene_gltf2_ue4.zip](https://cdn.discordapp.com/attachments/1135985731639181392/1203754525119488010/io_scene_gltf2_ue4.zip?ex=6738d6c3&is=67378543&hm=ff256b4188eb7ceb2f4b25ef501f5bb79264f7841c0fbe7eb58adcb37036b88b&).
3. Rename MIs in the custom mesh to match the target mesh using JSON data exported via fmodel.
   - Ensure the custom mesh has at least as many MIs as the target mesh.  I generally recommend matching the MI names to the target JSON MI names exactly.  You can use [my script here](https://github.com/peek6/Json2DA/blob/b23198f47a2a57f9acc9727b2889918251ff5d25/change_blender_material_names.py) to automatically import the target MI names onto your Blender mesh if you modify the mesh_json_path to point to the target mesh's JSON file extracted using Fmodel. 
4. Align the custom mesh to the target mesh (e.g., using [this video guide](https://www.youtube.com/watch?v=XZ748t5KQv8) from 5:37–14:56).
5. Rename the target skeleton to `Armature` and parent the custom mesh to it.
6. Delete all weights from the custom mesh, then transfer weights from the target mesh (refer to [this video](https://www.youtube.com/watch?v=bR_Vke__voU)).
7. Export the updated mesh as FBX using [this plugin](https://github.com/matyalatte/blender3d_import_psk_psa/releases).

### Step 3: Import to Unreal Engine

1. Import the FBX into Unreal Engine so that it has the exact same folder path and name as the original game's target mesh you want to replace.
2. Open the skeletal mesh and point the MIs and skeleton to UE assets which exactly match the skeleton and MI paths and names from the target mesh's JSON file.
3. Include only the mesh in the chunk, excluding skeletons and excluding MIs (unless you want to modify the MIs).
4. If your target mesh does not have a PRP, you are basically done.  Package the mod in UE, and skip to the mod installation step below.

### Step 4: Additional Steps for PRP Targets
If the target mesh also has PRP:
1. Import the target PRP GLTF into the same Blender project/window as above.
2. Rename the skeleton from above to anything other than `Armature` (for example, rename it as `Armature MSL`), and then rename the PRP skeleton you just imported to `Armature`.
3. Re-parent the EXACT SAME MSL mesh you exported above to the PRP skeleton's armature (the one you just renamed `Armature`).
4. Delete your custom mesh's weights, transfer weights from the imported target PRP mesh to your custom mesh (referring again to [this video](https://www.youtube.com/watch?v=bR_Vke__voU)), and export your new custom PRP mesh as FBX using [this plugin](https://github.com/matyalatte/blender3d_import_psk_psa/releases).
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
3. Grab the [Custom UE 5.2 engine](https://drive.google.com/drive/folders/1TUmRc7qTq1xTUkGcWnPz6-2KuA4RTPOf), make sure you set it to open in the [Custom UE 5.2 engine](https://drive.google.com/drive/folders/1TUmRc7qTq1xTUkGcWnPz6-2KuA4RTPOf), and set project/editor settings as described in [this guide](https://modding.wiki/en/hogwartslegacy/developers/getting-started).  You can now import most types of assets into the game as follows:
     - create the asset in UE by right-clicking within your desired folder and picking the asset type you want from the "Polaris" Menu.
     - right-click the asset you just created, select "scripted asset actions" and select "Import JSON" then browse to the corresponding JSON you extracted using [fmodel](https://fmodel.app/)
4. Place all of your custom meshes, textures, and MIs in a new dedicated folder (for example, in Content/Mods/your_mod_name).
5. In the same dedicated folder, create the following assets:
   - **BaseItem (BI):** Points to your custom mesh.  What I'll typically do is import an existing BI for a similar outfit and then modify it to point to my custom mesh.
   - **CustomizeItem (CI):** Defines coloring slots for MIs.  Again I usually start by importing one from the original game which has the coloring slots for its MIs set up as I want, and modify it as needed to point to any new MIs I've made.
   - **BaseCharacterItem (BCI):** Just create a blank one.
6. Overwrite the original IP for the desired slot:
   - Modify it to point to your custom BI, CI, and BCI.
7. Package the mod:
   - Include the IP and all custom assets in your chunk.  You can easily do this by creating a [primary asset label](https://dev.epicgames.com/documentation/en-us/unreal-engine/cooking-content-and-creating-chunks-in-unreal-engine?application_version=5.4) in your mod directory, checking the box to label all assets in your directory, and adding your IP as an explicit asset.  Then just package in UE as usual. 
   - Place your packaged mod into the `LogicMods` directory and ensure all filenames end with `_P`. You can automate this with my [Python script](https://github.com/peek6/Json2DA/blob/tekken8/ue_mod_installer.py) provided in the custom project.

Note that the only original T8 asset you are modifying with this approach is the IP. Everything else can (and should) be under your own custom directory for this mod.

As a bonus, if you followed the above approach, I included a Python script in Content/Python/outfit_selector.py which will allow you to let players choose which custom part they want to replace. Follow the instructions I gave in the script's comments detailing how it should be setup and used.

---

Enjoy modding *Tekken 8*!
