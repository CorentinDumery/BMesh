#ifndef BASICIO_H
#define BASICIO_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDataStream>
#include <cfloat>
#include <cmath>
#include <cassert>



namespace StupidPointDontUseThatEverEverEver{
struct Point3f
{
    typedef float type_t;

    Point3f() :x(0),y(0),z(0) {}

    Point3f(float xI, float yI, float zI)
        :x(xI)
        ,y(yI)
        ,z(zI)
    {
        pos[0] = xI;
        pos[1] = yI;
        pos[2] = zI;
    }

    float operator[]( unsigned int i )const
    {
        return pos[i];
    }
    float & operator[]( unsigned int i )
    {
        return pos[i];
    }

    union
    {
        struct
        {
            float x;
            float y;
            float z;
        };
        float pos[3];
    };
};
}





namespace OFFIO{
template< class point_t , class tri_t > bool openTriMesh( const std::string & filename ,
                                                    std::vector< point_t > & vertices ,
                                                    std::vector< tri_t > & faces,
                                                          bool randomize = false)
{
    std::ifstream myfile;
    myfile.open(filename.c_str());
    if (!myfile.is_open())
    {
        std::cout << filename << " cannot be opened" << std::endl;
        return false;
    }

    std::string magic_s;

    myfile >> magic_s;

    if( magic_s != "OFF" )
    {
        std::cout << magic_s << " != OFF :   We handle ONLY *.off files." << std::endl;
        myfile.close();
        return false;
    }

    int n_vertices , n_faces , dummy_int;
    myfile >> n_vertices >> n_faces >> dummy_int;

    vertices.resize(n_vertices);

    for( int v = 0 ; v < n_vertices ; ++v )
    {
        double x , y , z;
        myfile >> x >> y >> z;
        vertices[v] = point_t( x , y , z );
    }


    for( int f = 0 ; f < n_faces ; ++f )
    {
        int n_vertices_on_face;
        myfile >> n_vertices_on_face;
        if( n_vertices_on_face == 3 )
        {
            tri_t tri;
            myfile >> tri[0] >> tri[1] >> tri[2];
            faces.push_back( tri );
        }
        else if( n_vertices_on_face > 3 )
        {
            std::vector< unsigned int > vhandles;
            vhandles.resize(n_vertices_on_face);
            for( int i=0 ; i < n_vertices_on_face ; ++i )
                myfile >> vhandles[i];

            // convert to triangles :
            {
                unsigned int k=(randomize)?(rand()%vhandles.size()):0;
                for (unsigned int i=0;i<vhandles.size()-2;++i)
                {
                    tri_t tri;
                    tri[0]=vhandles[(k+0)%vhandles.size()];
                    tri[1]=vhandles[(k+i+1)%vhandles.size()];
                    tri[2]=vhandles[(k+i+2)%vhandles.size()];
                    faces.push_back(tri);
                }
            }
        }
    }

    myfile.close();
    return true;
}



template< class point_t , class face_t > bool save( const std::string & filename , std::vector< point_t > & vertices , std::vector< face_t > & faces )
{
    std::ofstream myfile;
    myfile.open(filename.c_str());
    if (!myfile.is_open())
    {
        std::cout << filename << " cannot be opened" << std::endl;
        return false;
    }

    myfile << "OFF" << std::endl;

    unsigned int n_vertices = vertices.size() , n_faces = faces.size();
    myfile << n_vertices << " " << n_faces << " 0" << std::endl;

    for( unsigned int v = 0 ; v < n_vertices ; ++v )
    {
        myfile << vertices[v][0] << " " << vertices[v][1] << " " << vertices[v][2] << std::endl;
    }
    for( unsigned int f = 0 ; f < n_faces ; ++f )
    {
        myfile << faces[f].size();
        for( unsigned int vof = 0 ; vof < faces[f].size() ; ++vof )
            myfile << " " << faces[f][vof];
        myfile << std::endl;
    }
    myfile.close();
    return true;
}
}






namespace OBJIO{

template< class point_t , class tri_t > bool openTriMesh(
        const std::string & filename,
        std::vector< point_t > & vertices,
        std::vector< tri_t > & faces,
        bool randomize = false)
{
    std::ifstream myfile;
    myfile.open(filename.c_str());
    if (!myfile.is_open())
    {
        std::cout << filename << " cannot be opened" << std::endl;
        return false;
    }

    vertices.clear();
    faces.clear();

    while( myfile.good() )
    {
        std::string line;
        getline (myfile,line);
        QString QTLine = QString::fromStdString( line );
        QRegExp reg("\\s+");
        QStringList lineElements = QTLine.split(reg);

        if(  lineElements.size() > 0  )
        {
            QString elementType = lineElements[0];
            // vertex
            if ( elementType == QString("v") )
            {
                vertices.push_back(point_t( lineElements[1].toDouble() , lineElements[2].toDouble() , lineElements[3].toDouble() ));
            }
            // face
            else if ( elementType == QString("f") )
            {
                std::vector< unsigned int > vhandles;
                for( int i = 1 ; i < lineElements.size() ; ++i )
                {
                    QStringList FaceElements = lineElements[i].split("/", QString::SkipEmptyParts);
                    if( FaceElements.size() > 0 )
                        vhandles.push_back( (unsigned int)( (abs(FaceElements[0].toInt()) - 1) ) );
                }

                if (vhandles.size()>3)
                {
                    // convert to triangles :
                    {
                        //model is not triangulated, so let us do this on the fly...
                        //to have a more uniform mesh, we add randomization
                        unsigned int k=(randomize)?(rand()%vhandles.size()):0;
                        for (unsigned int i=0;i<vhandles.size()-2;++i)
                        {
                            tri_t tri;
                            tri[0] = vhandles[(k+0)%vhandles.size()];
                            tri[1] = vhandles[(k+i+1)%vhandles.size()];
                            tri[2] = vhandles[(k+i+2)%vhandles.size()];
                            faces.push_back(tri);
                        }
                    }
                }
                else if (vhandles.size()==3)
                {
                    tri_t tri;
                    tri[0]= vhandles[0];
                    tri[1]= vhandles[1];
                    tri[2]= vhandles[2];
                    faces.push_back(tri);
                }
            }
        }
    }
    myfile.close();
    return true;
}



template< class point_t , typename face_t > bool save(
        std::string const & filename,
        std::vector< point_t > & verticesP,
        std::vector< face_t > & facesP )
{
    std::ofstream myfile;
    myfile.open(filename.c_str());
    if (!myfile.is_open())
    {
        std::cout << filename << " cannot be opened" << std::endl;
        return false;
    }

    myfile << "#OBJ" << std::endl;
    myfile << (verticesP.size()) << " " << (facesP.size()) << " 0" << std::endl;

    for( unsigned int v = 0 ; v < verticesP.size() ; ++v )
    {
        myfile << "v " << (verticesP[v][0]) << " " << (verticesP[v][1]) << " " << (verticesP[v][2]) << std::endl;
    }

    for( unsigned int t = 0 ; t < facesP.size() ; ++t )
    {
        unsigned int nv = facesP[t].size();
        myfile << "f";
        for( unsigned int vof = 0 ; vof < nv ; ++vof )
            myfile << " " << (facesP[t][vof] + 1);
        myfile << std::endl;
    }

    myfile.close();
    return true;
}
}



#endif // BASICIO_H
