#include <cub.h>

cub::cub()
{
    qDebug() <<"Estic en el constructor del cub\n";
    // Cub centrat al 0,0,0 amb dimensió 1 a totes les seves arestes
    xorig = -0.5; yorig = -0.50; zorig = -0.5;
    a = 1.0;
    h = 1.0;
    p = 1.0;

    // Vertices of a unit cube centered at origin, sides aligned with axes
    vertices[0] = point4( -0.5, -0.5,  0.5, 1.0 );
    vertices[1] = point4( -0.5,  0.5,  0.5, 1.0 );
    vertices[2] = point4(  0.5,  0.5,  0.5, 1.0 );
    vertices[3] = point4(  0.5, -0.5,  0.5, 1.0 );
    vertices[4] = point4( -0.5, -0.5, -0.5, 1.0 );
    vertices[5] = point4( -0.5,  0.5, -0.5, 1.0 );
    vertices[6] = point4(  0.5,  0.5, -0.5, 1.0 );
    vertices[7] = point4(  0.5, -0.5, -0.5, 1.0 );

    // RGBA colors
    vertex_colors[0] =    color4( 0.0, 0.0, 0.0, 1.0 );  // black
    vertex_colors[1] =    color4( 1.0, 0.0, 0.0, 1.0 );  // red
    vertex_colors[2] =    color4( 1.0, 1.0, 0.0, 1.0 );  // yellow
    vertex_colors[3] =    color4( 0.0, 1.0, 0.0, 1.0 );  // green
    vertex_colors[4] =    color4( 0.0, 0.0, 1.0, 1.0 );  // blue
    vertex_colors[5] =    color4( 1.0, 0.0, 1.0, 1.0 );  // magenta
    vertex_colors[6] =    color4( 1.0, 1.0, 1.0, 1.0 );  // white
    vertex_colors[7] =    color4( 0.0, 1.0, 1.0, 1.0 );  // cyan



}

// Constructora amb tots els parametres
cub::cub(int an, int al, int profu, const GLfloat x0, GLfloat y0, GLfloat z0)
{
    qDebug() <<"Estic en el constructor parametritzat del cub\n";
    a = an;
    h = al;
    p = profu;
    xorig = x0;
    yorig = y0;
    zorig = z0;
}

// Destructora
cub::~cub()
{
}

// quad generates two triangles for each face and assigns colors
//    to the vertices

void cub::quad( int a, int b, int c, int d )
{
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a];
    vertexsTextura[Index] = vec2(0.0, 0.0); Index++;
    colors[Index] = vertex_colors[b]; points[Index] = vertices[b];
    vertexsTextura[Index] = vec2(1.0, 0.0); Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c];
    vertexsTextura[Index] = vec2(1.0, 1.0); Index++;
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a];
    vertexsTextura[Index] = vec2(0.0, 0.0); Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c];
    vertexsTextura[Index] = vec2(1.0, 1.0); Index++;
    colors[Index] = vertex_colors[d]; points[Index] = vertices[d];
    vertexsTextura[Index] = vec2(0.0, 1.0); Index++;
}


// Realitzacio de la geometria del cub en una genList o en el vertex array, segons el que visualitzem

void cub::make()
{
     qDebug() <<"Estic en el make del cub\n";
    // generacio de la geometria dels triangles per a visualitzar-lo
    Index = 0;
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
    initTextura();

}

void cub::initTextura()
 {
     qDebug() << "Initializing textures...\n";


     // Carregar la textura
     glActiveTexture(GL_TEXTURE0);
     texture = new QOpenGLTexture(QImage("://resources/mosaic.png"));
     texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
     texture->setMagnificationFilter(QOpenGLTexture::Linear);

     texture->bind(0);

 }

// Carrega a la GPU del cub

void cub::toGPU(QGLShaderProgram *program){
    qDebug() << "Passo el Cub a la GPU.....\n";

    // S'activa la textura i es passa a la GPU
    texture->bind(0);
    program->setUniformValue("texMap", 0);

    // Creació d'un vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Creacio i inicialitzacio d'un vertex buffer object (VBO)
    glGenBuffers( 1, &buffer );

    // Activació a GL del Vertex Buffer Object
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // Transferència dels punts, colors i coordenades de textura al vertex buffer object
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors)+sizeof(vertexsTextura),
                  NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points)+sizeof(colors), sizeof(vertexsTextura), vertexsTextura );


    // set up vertex arrays

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,  0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(points)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(points)+sizeof(colors)));
    glEnableVertexAttribArray(2);


    glEnable( GL_DEPTH_TEST );
    glEnable(GL_TEXTURE_2D);


}


void cub::draw()
{

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );
}

void cub::aplicaTG(mat4 m)
{
    point4  transformed_points[NumVertices];

    for ( int i = 0; i < NumVertices; ++i ) {
        transformed_points[i] = m * points[i];
    }

    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    // Actualitzacio del vertex array per a preparar per pintar
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(transformed_points),
                     transformed_points );


}
