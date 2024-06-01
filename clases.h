#include <cstdio>
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
        int size;
        T* arr;
    public:
        Arreglo() {
            len = 0;
            size = 20;
            arr = new T[size];
        }

        int length() {return len;}

        void operator+(T elem) {
            if (len >= size) {
                size += 20;
                T* new_arr = new T[size];

                for (int i = 0; i < len; i++) {
                    new_arr[i] = arr[i];
                }

                arr = new_arr;
            }

            arr[len++] = elem;
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

        string getNombre() {
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

        void comentar(Comentario com) {comentarios + com;}
        int getCantidadComentarios() {return comentarios.length();}
};

class FileOpenException : public exception {
    private:
        string msg;
    public:
        FileOpenException(string _msg) {
            msg = "no se pudo abrir el archivo '" + _msg + "'";
        }

        string gerMessage() {return msg;}
};

class RecordNotFound : public exception {
    private:
        string msg;
    public:
        RecordNotFound(string _msg) {
            msg = "no se encontró registro para el dato '" + _msg + "'";
        }
        
        string gerMessage() {return msg;}
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
            ifstream file(USERS_PATH);
            if(!file) throw FileOpenException(USERS_PATH);

            string nombre;
            int dni, edad;

            while(!file.eof()) {
                file >> edad;
                file >> dni;
                file.ignore();
                getline(file, nombre);

                if (dni != usuarios[usuarios.length()-1].getDNI()) usuarios + Usuario(nombre, dni, edad);
            }
            file.close();
        }

        void cargar_autores() {
            ifstream file(AUTHORS_PATH);
            if(!file) throw FileOpenException(AUTHORS_PATH);

            string nombre, medio;
            int dni;

            while(!file.eof()) {
                file >> dni;
                file.ignore();
                getline(file, nombre);
                getline(file, medio);

                if (dni != autores[autores.length()-1].getDNI()) autores + Autor(nombre, dni, medio);
            }
            file.close();
        }

        void cargar_comentarios() {
            ifstream file(COMMENTS_PATH);
            if(!file) throw FileOpenException(COMMENTS_PATH);

            string texto;
            int numero, dni_usuario;
            
            while(!file.eof()) {
                file >> numero;
                file >> dni_usuario;
                file.ignore();
                getline(file, texto);

                if (dni_usuario != comentarios[comentarios.length()-1].getUsuario().getDNI()) comentarios + Comentario(numero, texto, buscar_usuario(dni_usuario));
            }
            file.close();
        }

        void cargar_noticias() {
            ifstream file(NEWS_PATH);
            if(!file) throw FileOpenException(NEWS_PATH);

            string titulo, detalle;
            Fecha publicacion;
            int dni_autor, numero;

            while(!file.eof()) {
                file >> publicacion.dia;
                file >> publicacion.mes;
                file >> publicacion.anio;
                file >> dni_autor;
                file >> numero;
                file.ignore();
                getline(file, titulo);
                getline(file, detalle);

                if (titulo != noticias[noticias.length()-1].getTitulo()) noticias + Noticia(titulo, detalle, publicacion, buscar_autor(dni_autor), buscar_comentarios(numero));
            }
            file.close();
        }

        void guardar_usuarios() {
            ofstream file(USERS_PATH);
            if(!file.is_open()) throw FileOpenException(USERS_PATH);

            for (int i = 0; i < usuarios.length(); i++) {
                file << usuarios[i].getEdad() << " "
                << usuarios[i].getDNI() << " "
                << usuarios[i].getNombre() << endl;
            }

            file.close();
        }
        
        void guardar_autores() {
            ofstream file(AUTHORS_PATH);
            if(!file.is_open()) throw FileOpenException(AUTHORS_PATH);

            for (int i = 0; i < autores.length(); i++) {
                file << autores[i].getDNI() << endl
                << autores[i].getNombre() << endl
                << autores[i].getMedio() << endl;
            }

            file.close();
        }

        void guardar_comentarios() {
            ofstream file(COMMENTS_PATH);
            if(!file.is_open()) throw FileOpenException(COMMENTS_PATH);

            for (int i = 0; i < comentarios.length(); i++) {
                file << comentarios[i].getNumero() << " "
                << comentarios[i].getUsuario().getDNI() << " "
                << comentarios[i].getTexto() << endl;
            }

            file.close();
        }

        void guardar_noticias() {
            ofstream file(NEWS_PATH);
            if(!file.is_open()) throw FileOpenException(NEWS_PATH);

            for (int i = 0; i < noticias.length(); i++) {
                file << noticias[i].getPublicado().dia << " "
                << noticias[i].getPublicado().mes << " "
                << noticias[i].getPublicado().anio << " "
                << noticias[i].getAutor().getDNI() << " "
                << i+1 << endl
                << noticias[i].getTitulo() << endl
                << noticias[i].getDetalle() << endl;
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

        Arreglo<Comentario> buscar_comentarios(int numero) {
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

        Noticia buscar_noticia(string titulo) {
            for (int i = 0; i < noticias.length(); i++) {
                if(noticias[i].getTitulo() == titulo) return noticias[i];
            }

            throw RecordNotFound(titulo);
        }

        // TODO: no se que tan bien implementado está esto :/
        bool aniadir_noticia(Noticia n) {
            try {
                buscar_noticia(n.getTitulo());
                return false;
            } catch (RecordNotFound& e) {
                noticias + n;
                return true;
            }
        }

        bool aniadir_usuario(Usuario u) {
            try {
                buscar_usuario(u.getDNI());
                return false;
            } catch (RecordNotFound& e) {
                usuarios + u;
                return true;
            }
        }

        bool aniadir_autor(Autor a) {
            try {
                buscar_autor(a.getDNI());
                return false;
            } catch (RecordNotFound& e) {
                autores + a;
                return true;
            }
        }

        Arreglo<Usuario> getUsuarios() {return usuarios;}
        Arreglo<Autor> getAutores() {return autores;}
        Arreglo<Comentario> getComentarios() {return comentarios;}
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
