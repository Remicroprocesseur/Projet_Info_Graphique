#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

int main()
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile("models/Mutant Run.fbx", aiProcess_Triangulate);
    if (!scene)
    {
        std::cerr << "Erreur Assimp: " << importer.GetErrorString() << std::endl;
        return -1;
    }
    std::cout << "Modèle chargé avec succès !" << std::endl;
    return 0;
}
