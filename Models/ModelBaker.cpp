#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <unordered_map>
#include <filesystem>
#include <iterator>
#include <algorithm>
 

struct Point4
{
    double x;
    double y;
    double z;
    double w;
};

struct Point3
{
    double x;
    double y;
    double z;
};

struct Point2
{
    double x;
    double y;
};

struct Material
{
    std::string name;
    std::string diffuseTexture;
    Point3 ambient;
    Point3 diffuse;
    Point3 specular;
    Point3 emissive;
    double specularHighlight;
    double indexOfRefraction;
    double opacity;
};

struct Vertex
{
    Point3 pos;
    Point3 normal;
    bool operator==( const Vertex & v) const
    {
        return pos.x == v.pos.x && pos.y == v.pos.y && pos.z == v.pos.z && 
            normal.x == v.normal.x && normal.y == v.normal.y && normal.z == v.normal.z;
    }
};

void printMaterials(const std::vector<Material> &materials)
{
    for( int mat = 0; mat < materials.size(); ++mat )
    {
        std::cout << materials[mat].name <<":"<< std::endl;
        std::cout << "Texture: " << materials[mat].diffuseTexture << std::endl;
        std::cout << "Ambient: <" << materials[mat].ambient.x <<","<< materials[mat].ambient.y<<","<< materials[mat].ambient.z<<">"<< std::endl;
        std::cout << "Diffuse: <" << materials[mat].diffuse.x <<","<< materials[mat].diffuse.y<<","<< materials[mat].diffuse.z<<">"<< std::endl;
        std::cout << "Specular: <" << materials[mat].specular.x <<","<< materials[mat].specular.y<<","<< materials[mat].specular.z<<">"<< std::endl;
        std::cout << "Emissive: <" << materials[mat].emissive.x <<","<< materials[mat].emissive.y<<","<< materials[mat].emissive.z<<">"<< std::endl;
        std::cout << "Specular Highlight: " << materials[mat].specularHighlight << std::endl;
        std::cout << "Index of Refraction: " << materials[mat].indexOfRefraction << std::endl;
        std::cout << "Opacity: " << materials[mat].opacity << std::endl;
    }
}

namespace std {
    template <>
        class hash<Point3>{
        public :
            size_t operator()(const Point3 &p ) const
            {
                return hash<double>()(p.x) ^ hash<double>()(p.y)^ hash<double>()(p.z);
            }
    };
    template <>
        class hash<Point4>{
        public :
            size_t operator()(const Point4 &p ) const
            {
                return hash<double>()(p.x) ^ hash<double>()(p.y)^ hash<double>()(p.z)^ hash<double>()(p.w);
            }
    };
    template <>
        class hash<Vertex>{
        public :
            size_t operator()(const Vertex &v ) const
            {
                return hash<Point3>()(v.pos) ^ hash<Point3>()(v.normal);
            }
    };
};

 
 
void read_directory(const std::string& name, std::vector<std::string>& v, std::vector<std::string>& v2, std::vector<std::string>& v3)
{
    std::filesystem::path p(name);
    std::filesystem::directory_iterator end;
    for (std::filesystem::directory_iterator it(p); it != end; ++it)
    {
        if(it->path().extension().string() == ".obj")
        {
            v.push_back(it->path().string());
            v2.push_back(it->path().stem().string());
            v3.push_back(it->path().parent_path().string());
        }
    }
}

int main()
{
    std::ofstream fout;
    fout.open("Models.h");
    
    std::vector<std::string> fileNames;
    std::vector<std::string> fileNamesNoExt;
    std::vector<std::string> fileNamesPath;
    read_directory("./JacobButton/", fileNames,fileNamesNoExt,fileNamesPath);
    read_directory("./ChristopherButton/", fileNames,fileNamesNoExt,fileNamesPath);
    for( uint32_t file = 0; file < fileNames.size(); ++file)
    {
        std::string vertexArrayName = fileNamesNoExt[file]+"Verts";
        std::string indexArrayName = fileNamesNoExt[file]+"Indices";
        std::ifstream fin(fileNames[file]);

        std::vector<Point3> verts;
        std::vector<Point3> normals;
        std::vector<Point2> texcoords;
        std::vector<Material> materials;

        std::vector<Vertex> mesh;
        std::vector<int> meshIndices;
        std::unordered_map<Vertex,int> vertexMapper;

        int currentMaterialIndex = -1;

        std::string line;
        while(std::getline(fin,line))
        {
            int div = line.find(" ");
            std::string firstWord = line.substr(0, div);
            std::stringstream ss(line.substr(div));
            if( firstWord=="mtllib" )
            {
                std::string fileName;
                ss >> fileName;
                std::ifstream matFin(fileNamesPath[file]+fileName);
                std::string matLine;
                while(std::getline(matFin,matLine))
                {
                    int matDiv = matLine.find(" ");
                    if( matDiv  < matLine.size() )
                    {
                        std::string matFirstWord = matLine.substr(0, matDiv);
                        std::stringstream matSS(matLine.substr(matDiv));
                        if(matFirstWord=="newmtl" )
                        {
                            Material mat;
                            matSS >> mat.name;
                            materials.push_back(mat);
                        }
                        else if(matFirstWord=="Ns" )
                        {
                            matSS >> materials.back().specularHighlight;
                        }
                        else if(matFirstWord=="Ka" )
                        {
                            matSS >> materials.back().ambient.x;
                            matSS >> materials.back().ambient.y;
                            matSS >> materials.back().ambient.z;
                        }
                        else if(matFirstWord=="Kd" )
                        {
                            matSS >> materials.back().diffuse.x;
                            matSS >> materials.back().diffuse.y;
                            matSS >> materials.back().diffuse.z;
                        }
                        else if(matFirstWord=="Ks" )
                        {
                            matSS >> materials.back().specular.x;
                            matSS >> materials.back().specular.y;
                            matSS >> materials.back().specular.z;
                        }
                        else if(matFirstWord=="Ke" )
                        {
                            matSS >> materials.back().emissive.x;
                            matSS >> materials.back().emissive.y;
                            matSS >> materials.back().emissive.z;
                        }
                        else if(matFirstWord=="Ni" )
                        {
                            matSS >> materials.back().indexOfRefraction;                     
                        }
                        else if(matFirstWord=="d" )
                        {
                            matSS >> materials.back().opacity;   
                        }
                        else if(matFirstWord=="illum" )
                        {

                        }
                        else if(matFirstWord=="map_Kd" )
                        {
                            matSS >> materials.back().diffuseTexture; 
                        }
                    }
                }
                matFin.close();
            }
            else if(firstWord=="v" )
            {
                Point3 p;
                ss >> p.x;
                ss >> p.y;
                ss >> p.z;
                verts.push_back(p);
            }
            else if(firstWord=="vn" )
            {
                Point3 p;
                ss >> p.x;
                ss >> p.y;
                ss >> p.z;
                normals.push_back(p);
            }
            else if(firstWord=="vt" )
            {
                Point2 p;
                ss >> p.x;
                ss >> p.y;
                texcoords.push_back(p);
            }
            else if(firstWord=="f" )
            {
                std::vector<std::string> faceVerts;
                std::string indexGrouped;
                while( ss >> indexGrouped )
                {
                    faceVerts.push_back( indexGrouped );
                }
                for( int face = 0; face < faceVerts.size(); ++face )
                {
                    std::stringstream faceVertCutter(faceVerts[face]);
                    std::string indexStr;
                    int indexindex = 0;

                    Vertex v;
                    while( std::getline( faceVertCutter,indexStr,'/'))
                    {
                        if( indexStr.size() > 0)
                        {
                            int index = std::stoi( indexStr );
                            if( index < 0 )
                            {
                                switch( indexindex )
                                {
                                    case 0:
                                    {
                                        index = verts.size() + index;
                                        break;
                                    }
                                    case 1:
                                    {
                                        break;
                                    }
                                    case 2:
                                    {
                                        index = normals.size() + index;
                                        break;
                                    }
                                }


                            }
                            else
                            {
                                index = index -1;
                            }
                            switch( indexindex )
                            {
                                case 0:
                                {
                                    v.pos = verts[index];
                                    break;
                                }
                                case 1:
                                {
                                    break;
                                }
                                case 2:
                                {
                                    v.normal = normals[index];
                                    break;
                                }
                                default:
                                {
                                    break;
                                }
                            }
                        }
                        ++indexindex;
                    }

                    if( vertexMapper.end() == vertexMapper.find( v ) )
                    {
                        mesh.push_back(v);
                        meshIndices.push_back(mesh.size()-1);
                        vertexMapper[v] = mesh.size()-1;
                    }
                    else
                    {
                        meshIndices.push_back(vertexMapper[v]);
                    }
                }
            }
            else if(firstWord=="usemtl" )
            {
                std::string matName;
                ss >> matName;
                for( int mat = 0; mat < materials.size(); ++mat )
                {
                    if( matName == materials[mat].name )
                    {
                        currentMaterialIndex = mat;
                        break;
                    }
                }
            }
            else if(firstWord=="s" )
            {
	    	//http://learnwebgl.brown37.net/10_surface_properties/smooth_vertex_normals.html
            }
            else if(firstWord=="o" )
            {
                //probably make new vertex pools here for each
            }
        }
        fin.close();

        //printMaterials(materials);

        fout << "float "<<vertexArrayName<<"[] ="<<std::endl<< "{"<<std::endl;
        for( int i = 0; i < mesh.size(); ++i)
        {
            fout << "\t"<< std::fixed << std::setprecision(6) << (mesh[i].pos.x < 0?"":" ")<<mesh[i].pos.x <<"f, " << (mesh[i].pos.y < 0?"":" ")<<mesh[i].pos.y <<"f, " << (mesh[i].pos.z < 0?"":" ")<<mesh[i].pos.z <<"f, ";
            fout << (mesh[i].normal.x < 0?"":" ") <<mesh[i].normal.x <<"f, " << (mesh[i].normal.y < 0?"":" ") <<mesh[i].normal.y <<"f, " << (mesh[i].normal.z < 0?"":" ") <<mesh[i].normal.z <<"f, ";
            fout << std::endl;
        }
        fout << "};"<<std::endl;

        int maxIndex = -1;
        for( int i = 0; i < meshIndices.size(); ++i)
        {
            if( meshIndices[i] > maxIndex)
            {
                maxIndex = meshIndices[i];
            }
        }
        double maxAmtOfIndexDigits = ceil(log10(maxIndex));
        if( meshIndices.size() > 2 )
        {
            fout << "uint32_t "<<indexArrayName<<"[] ="<<std::endl<< "{"<<std::endl;
            for( int i = 0; i < meshIndices.size(); i += 3)
            {
                fout << "\t" << std::setw(maxAmtOfIndexDigits) << meshIndices[i] << ", "<< std::setw(maxAmtOfIndexDigits) <<meshIndices[i+2] << ", "<< std::setw(maxAmtOfIndexDigits) <<meshIndices[i+1]  <<(((i+2) <meshIndices.size()-1)?",":"") << std::endl;
            }
            fout << "};"<<std::endl;
            fout << "uint32_t "<<indexArrayName<<"Count = "<< meshIndices.size()<<";" <<std::endl;
        }
        else
        {
            fout << "uint32_t "<<indexArrayName<<"Count = "<< 0<<";"<<std::endl;
        }
    }
    fout.close();
    return 0;
}
