
#include "mesh.hpp"

#include "mat4.hpp"

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <cmath>
#include <algorithm>

mesh load_off_file(const std::string& filename)
{

    std::vector<vec3> v_vertices;
    std::vector<int> v_connectivity;

    std::ifstream fid(filename.c_str());
    if(!fid.good())
    {
        std::cout<<"Cannot open file "+filename<<std::endl;
        abort();
    }

    std::string buffer;

    //find OFF header
    bool find_off=false;
    while(find_off==false)
    {
        if(!fid.good())
        {
            std::cout<<"Cannot find OFF header in file "+filename<<std::endl;
            abort();
        }
        std::getline(fid,buffer);
        if(buffer.find("OFF")!=std::string::npos)
            find_off=true;
    }

    //read number of vertices + triangles
    int N_vertex=0,N_triangle=0;
    std::getline(fid,buffer);
    std::stringstream tokens(buffer);
    tokens>>N_vertex>>N_triangle;


    //read vertices
    for(int k=0;k<N_vertex;++k)
    {
        std::getline(fid,buffer);
        if(buffer.size()>0 && buffer[0]=='#') {--k; continue;}

        vec3 p;
        std::stringstream tokens_vertices(buffer);
        tokens_vertices>>p.x>>p.y>>p.z;

        v_vertices.push_back(p);
    }

    //read connectivity
    for(int k=0;k<N_triangle;++k)
    {
        std::getline(fid,buffer);
        if(buffer.size()>0 && buffer[0]=='#') {--k; continue;}

        int N_size,u0,u1,u2;
        std::stringstream tokens_connectivity(buffer);
        tokens_connectivity>>N_size>>u0>>u1>>u2;


        if(N_size!=3)
        {
            std::cout<<"Cannot read OFF with non triangular faces for file "+filename<<std::endl;
            abort();
        }

        v_connectivity.push_back(u0);v_connectivity.push_back(u1);v_connectivity.push_back(u2);
    }

    fid.close();


    //fill vertex
    mesh m;
    m.vertex.resize(v_vertices.size());
    for(int k=0,N=v_vertices.size();k<N;++k)
    {
        vertex_opengl& v=m.vertex[k];
        v.position=v_vertices[k];
    }
    m.connectivity.resize(v_connectivity.size()/3);
    for(int k=0,N=v_connectivity.size()/3;k<N;++k)
    {
        triangle_index& c=m.connectivity[k];
        c.u0=v_connectivity[3*k+0];
        c.u1=v_connectivity[3*k+1];
        c.u2=v_connectivity[3*k+2];
    }
    return m;
}


mesh load_obj_file(const std::string& filename)
{
    std::vector<vec3> v_vertices;
    std::vector<vec2> v_texture;
    std::vector<triangle_index> v_connectivity;

    std::ifstream fid(filename.c_str());
    if(!fid.good())
      throw std::string("Cannot open file "+filename);

    std::string buffer;

    //read the whole file
    while(fid.good()==true)
    {
        //read line
        std::getline(fid,buffer);

        if(buffer.size()>0)
        {
            std::stringstream tokens_buffer(buffer);
            std::string first_word;
            tokens_buffer>>first_word;

            //vertices
            if(first_word=="v")
            {
                vec3 vertex;
                tokens_buffer>>vertex.x;
                tokens_buffer>>vertex.y;
                tokens_buffer>>vertex.z;

                v_vertices.push_back(vertex);
            }

            //texture
            if(first_word=="vt")
            {
                vec2 texture;
                tokens_buffer>>texture.x;
                tokens_buffer>>texture.y;

                v_texture.push_back(texture);
            }

            //connectivity


            if(first_word=="f")
            {
                int nbr_slash=std::count(buffer.begin(),buffer.end(),'/');
                int u0=0,u1=0,u2=0;
                if(nbr_slash==6) //coord/normal/texture
                {
                    std::string i0,i1,i2;
                    std::stringstream index;

                    tokens_buffer>>i0;
                    index.str(i0);
                    index>> u0;
                    tokens_buffer>>i1;
                    index.str(i1);
                    index>> u1;
                    tokens_buffer>>i2;
                    index.str(i2);
                    index>> u2;
                }
                else if(nbr_slash==0) //coord only
                {
                    tokens_buffer>>u0;
                    tokens_buffer>>u1;
                    tokens_buffer>>u2;
                }

                v_connectivity.push_back(triangle_index(u0-1,u1-1,u2-1));

            }

        }

    }


    mesh m;
    m.vertex.resize(v_vertices.size());
    for(int k=0,N=v_vertices.size();k<N;++k)
    {
        vertex_opengl& v=m.vertex[k];
        v.position=v_vertices[k];

    }
    for(int k=0,N=v_texture.size();k<N;++k)
    {
        vertex_opengl& t=m.vertex[k];
        t.texture=v_texture[k];
    }

    m.connectivity.resize(v_connectivity.size());
    for(int k=0,N=v_connectivity.size();k<N;++k)
    {
        triangle_index& c=m.connectivity[k];
        c.u0 = v_connectivity[k].u0;
        c.u1 = v_connectivity[k].u1;
        c.u2 = v_connectivity[k].u2;
    }

    return m;

}



void update_normals(mesh* m)
{
    const std::vector<triangle_index>& c=m->connectivity;

    //compute star
    std::map<int,std::list<int> > star;
    for(unsigned int k=0,N=c.size();k<N;++k)
    {
        const triangle_index& t=c[k];
        star[t.u0].push_back(k);
        star[t.u1].push_back(k);
        star[t.u2].push_back(k);
    }

    //compute per polygon normal
    std::vector<vec3> normal_polygon;
    normal_polygon.resize(m->connectivity.size());
    for(unsigned int k=0,N=m->connectivity.size();k<N;++k)
    {
        const triangle_index& t=m->connectivity[k];
        const vec3& p0=m->vertex[t.u0].position;
        const vec3& p1=m->vertex[t.u1].position;
        const vec3& p2=m->vertex[t.u2].position;

        const vec3 u0=normalize(p1-p0);
        const vec3 u1=normalize(p2-p0);
        const vec3 n=normalize(cross(u0,u1));

        normal_polygon[k]=n;
    }

    //compute per vertex normal
    for(unsigned int k=0,N=m->vertex.size();k<N;++k)
    {
        vec3 temp_normal;
        for(std::list<int>::const_iterator it=star[k].begin(),it_end=star[k].end();
            it!=it_end;++it)
            temp_normal += normal_polygon[*it];

        m->vertex[k].normal=normalize(temp_normal);
    }

}

void fill_color(mesh* m,const vec3& color)
{
    for(unsigned int k=0,N=m->vertex.size();k<N;++k)
        m->vertex[k].color=color;
}
void fill_color_normal(mesh* m)
{
    for(unsigned int k=0,N=m->vertex.size();k<N;++k)
    {
        const vec3& n=m->vertex[k].normal;
        m->vertex[k].color=vec3(fabs(n.x),fabs(n.y),fabs(n.z));
    }
}

void apply_deformation(mesh* m,const mat4 T)
{
    for(unsigned int k=0,N=m->vertex.size();k<N;++k)
    {
        vec3& v=m->vertex[k].position;
        v=T*v;
    }
}

void invert_normals(mesh* m)
{
    for(unsigned int k=0,N=m->vertex.size();k<N;++k)
        m->vertex[k].normal*=-1.0f;
}
