#include <exception>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Fecha {
    int dia, mes, anio;
};

template<class T>
class Arreglo {
    private:
        int len;
        T* arr;
    public:
        Arreglo() {
            len = 0;
            arr = new T[20];
        }

        int length() {return len;}

        void operator+(T elem) {
            arr[len++] = elem;
        }

        bool operator()(string str) {
            for (T* i = &arr[0]; i < &arr[0]+len; i++) {
                if (i->get() == str) return true;
            }

            return false;
        }
        
        T operator[](int n) {
            return arr[n];
        }
};

class Persona {
    private:
        string nombre;
        int dni;
    public:
        Persona() {};
        Persona(string _nombre, int _dni) : nombre(_nombre), dni(_dni) {};

        string get() {
            return nombre;
        }
        int getDNI(){
            return dni;
        }
};

class Autor : public Persona {
    private:
        string medio;
    public:
        Autor() {};
        Autor(string _nombre, int _dni, string _medio) : Persona(_nombre, _dni), medio(_medio) {};

        string getMedio() {return medio;}
};

class Usuario : public Persona {
    private:
        int edad;
    public:
        Usuario() {};
        Usuario(string _nombre, int _dni, int _edad) : Persona(_nombre, _dni), edad(_edad) {};

        int getEdad() {return edad;}
};

class Comentario {
    private:
        int numero;
        string texto;
        Usuario usuario;
    public:
        Comentario() {};
        Comentario(int _numero, string _texto, Usuario _usuario) : numero(_numero), texto(_texto), usuario(_usuario) {};

        int getNumero() {return numero;}
        string getTexto() {return texto;}
        Usuario getUsuario() {return usuario;}
};

class Noticia {
    private:
        string titulo, detalle;
        Fecha publicado;
        Autor autor;
        Arreglo<Comentario> comentarios;
    public:
        Noticia() {};
        Noticia(string _titulo, string _detalle, Fecha _publicacion, Autor _autor) {
            titulo = _titulo;
            detalle = _detalle;
            publicado = _publicacion;
            autor = _autor;
            comentarios = Arreglo<Comentario>(); // TODO: ¿se puede instanciar así?
        };
        
        Noticia(string _titulo, string _detalle, Fecha _publicacion, Autor _autor, Arreglo<Comentario> _comentarios) {
            titulo = _titulo;
            detalle = _detalle;
            publicado = _publicacion;
            autor = _autor;
            comentarios = _comentarios;
        };

        string getTitulo() {return titulo;}
        string getDetalle() {return detalle;}
        Fecha getPublicado() {return publicado;}
        Autor getAutor() {return autor;}
        Arreglo<Comentario> getComentarios() {return comentarios;}
        int getCantidadComentarios() {return comentarios.length();}

        void comentar(Comentario com) {
            comentarios + com;
        }

        string get() {
            return titulo;
        }
};

class FileOpenException : public exception {
    private:
        string msg;
    public:
        FileOpenException(string _msg) {
            msg = "no se pudo abrir el archivo '" + _msg + "'";
        }
};

class RecordNotFound : public exception {
    private:
        string msg;
    public:
        RecordNotFound(string _msg) {
            msg = "no se encontró registro para el dato '" + _msg + "'";
        }
};

class Data_manager {
    private:
        Arreglo<Usuario> usuarios;
        Arreglo<Autor> autores;
        Arreglo<Comentario> comentarios;
        Arreglo<Noticia> noticias;

        string USERS_PATH = "usuarios.csv";
        string AUTHORS_PATH = "autores.csv";
        string COMMENTS_PATH = "comentarios.csv";
        string NEWS_PATH = "noticias.csv";

        void cargar_usuarios() {
            ifstream users_file(USERS_PATH);
            if(!users_file) throw FileOpenException(USERS_PATH);

            string nombre;
            int dni, edad;
            
            while(!users_file.eof()) {
                users_file >> nombre;
                users_file >> edad;
                users_file >> dni;

                usuarios + Usuario(nombre, dni, edad);
            }
            users_file.close();
        }

        void cargar_autores() {
            ifstream authors_file(AUTHORS_PATH);
            if(!authors_file) throw FileOpenException(AUTHORS_PATH);

            string nombre, medio;
            int dni;
            
            while(!authors_file.eof()) {
                authors_file >> nombre;
                authors_file >> medio;
                authors_file >> dni;

                autores + Autor(nombre, dni, medio);
            }
            authors_file.close();
        }

        void cargar_comentarios() {
            ifstream comments_file(COMMENTS_PATH);
            if(!comments_file) throw FileOpenException(COMMENTS_PATH);

            string texto;
            int numero, dni_usuario;
            
            while(!comments_file.eof()) {
                comments_file >> numero;
                comments_file >> texto;
                comments_file >> dni_usuario;

                comentarios + Comentario(numero, texto, buscar_usuario(dni_usuario));
            }
            comments_file.close();
        }

        void cargar_noticias() {
            ifstream news_file(NEWS_PATH);
            if(!news_file) throw FileOpenException(NEWS_PATH);

            string titulo, detalle;
            Fecha publicacion;
            int dni_autor, numero;
            
            while(!news_file.eof()) {
                news_file >> titulo;
                news_file >> detalle;
                news_file >> publicacion.dia;
                news_file >> publicacion.mes;
                news_file >> publicacion.anio;
                news_file >> dni_autor;
                news_file >> numero;

                noticias + Noticia(titulo, detalle, publicacion, buscar_autor(dni_autor), buscar_comentario(numero));
            }
            news_file.close();
        }

        void guardar_usuarios() {
            ofstream file(USERS_PATH);
            if(!file.is_open()) throw FileOpenException(USERS_PATH);

            for (int i = 0; i < usuarios.length(); i++) {
                file << usuarios[i].get()
                << usuarios[i].getEdad()
                << usuarios[i].getDNI()
                << endl;
            }

            file.close();
        }
        
        void guardar_autores() {
            ofstream file(AUTHORS_PATH);
            if(!file.is_open()) throw FileOpenException(AUTHORS_PATH);

            for (int i = 0; i < autores.length(); i++) {
                file << autores[i].get()
                << autores[i].getMedio()
                << autores[i].getDNI()
                << endl;
            }

            file.close();
        }

        void guardar_comentarios() {
            ofstream file(COMMENTS_PATH);
            if(!file.is_open()) throw FileOpenException(COMMENTS_PATH);

            for (int i = 0; i < comentarios.length(); i++) {
                file << comentarios[i].getNumero()
                << comentarios[i].getTexto()
                << comentarios[i].getUsuario().getDNI()
                << endl;
            }

            file.close();
        }

        void guardar_noticias() {
            ofstream file(NEWS_PATH);
            if(!file.is_open()) throw FileOpenException(NEWS_PATH);

            for (int i = 0; i < noticias.length(); i++) {
                file << noticias[i].getTitulo()
                << noticias[i].getDetalle()
                << noticias[i].getPublicado().dia
                << noticias[i].getPublicado().mes
                << noticias[i].getPublicado().anio
                << noticias[i].getAutor().getDNI()
                << i
                << endl;
            }

            file.close();
        }
    public:
        Data_manager() {
            cargar_usuarios();
            cargar_autores();
            cargar_comentarios();
            cargar_noticias();
        }

        Arreglo<Comentario> buscar_comentario(int numero) {
            Arreglo<Comentario> resultados;

            for (int i = 0; i < comentarios.length(); i++) {
                if(comentarios[i].getNumero() == numero) {
                    resultados + comentarios[i];
                }
            }

            return resultados;
        }

        Usuario buscar_usuario(int dni) {
            for (int i = 0; i < usuarios.length(); i++) {
                if(usuarios[i].getDNI() == dni) return usuarios[i];
            }

            throw RecordNotFound(to_string(dni));
        }
        
        Autor buscar_autor(int dni) {
            for (int i = 0; i < autores.length(); i++) {
                if(autores[i].getDNI() == dni) return autores[i];
            }

            throw RecordNotFound(to_string(dni));
        }

        bool aniadir_noticia(Noticia n) {
            if(noticias(n.get())) return false;

            noticias + n;
            return true;
        }

        bool aniadir_usuario(Usuario u) {
            if(usuarios(u.get())) return false;

            usuarios + u;
            return true;
        }

        bool aniadir_autor(Autor a) {
            if(autores(a.get())) return false;

            autores + a;
            return true;
        }

        Arreglo<Noticia> getNoticias() {return noticias;}

        void guardar_cambios() {
            guardar_usuarios();
            guardar_autores();
            guardar_comentarios();
            guardar_noticias();
        }
};

class NEWS {
    private:
        Data_manager database;
    public:
        NEWS() {
            database = Data_manager();
        }

        Arreglo<Noticia> getNoticias() {return database.getNoticias();}

        bool publicar(Noticia n) {
            return database.aniadir_noticia(n);
        }

        bool registrar_usuario(Usuario user) {
            return database.aniadir_usuario(user);
        }

        bool registrar_autor(Autor aut){
            return database.aniadir_autor(aut);
        }

        ~NEWS() {
            database.guardar_cambios();
        }
};
