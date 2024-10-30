model_t model(const char* filename, int flags) {
    int aiFlags = 0
   //| aiProcess_FlipUVs
   | aiProcessPreset_TargetRealtime_MaxQuality
   //| aiProcessPreset_TargetRealtime_Quality
   //| aiProcessPreset_TargetRealtime_Fast
   //| aiProcess_ConvertToLeftHanded // D3D
   | aiProcess_LimitBoneWeights //(4, defined as AI_LMW_MAX_WEIGHTS in config.h)
   | aiProcess_JoinIdenticalVertices 
   | aiProcess_RemoveRedundantMaterials
   | aiProcess_ImproveCacheLocality 
   | aiProcess_OptimizeGraph
   | aiProcess_OptimizeMeshes
   | aiProcess_SplitLargeMeshes;

    model_t mo = {0};
    const struct aiScene* scene = aiImportFile(filename, flags);
    if( scene ) {
        mo.mesh = REALLOC(0, sizeof(mesh_t) * (mo.mesh_count = scene->mNumMeshes) );
        for( int i = 0; i < mo.mesh_count; ++i ) {
            const struct aiMesh* m = scene->mMeshes[i];
            mo.mesh[i] = mesh(m, flags);
        }
        aiReleaseImport(scene);
    }
    return mo;
}
