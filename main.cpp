#include <iostream>

// rand
#include <stdlib.h>
#include <time.h>


// classes herdadadas (figura implicito)
#include "circulo.h"
#include "triangulo.h"

#define MAX_OBJS 100

#ifdef _WIN32
    // detectar mouse windows
    #include <windows.h>
    static bool hold_previous = false;

    int detect_mouse(int fd)
    {
        bool clicked = false;
        bool hold = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;

        if (hold && !hold_previous)
        {
            clicked = true;
        }

        return clicked;
    }
    void global_sleep(int t)
    {
        t = t/1000;
        Sleep(t);
    }

    int open_mouse()
    {
        return 1;
    }

    void close_mouse(int fd)
    {
        return ;
    }
#else
    // detectar mouse linux
    #include <fcntl.h>
    #include <unistd.h>
    #include <linux/input.h>
    #include <cstring>
    #include <dirent.h>

    std::string find_mouse_input();

    int detect_mouse(int fd)
    {
        struct input_event ev;

        bool click = false;
        while (read(fd, &ev, sizeof(struct input_event)) > 0)
        {
            if (ev.type == EV_KEY && ev.code == BTN_LEFT && ev.value == 1)
                click = true;
        }

        return click;
    }

    void global_sleep(int t)
    {
        usleep(t);
    }

    int open_mouse()
    {
        std::string path_str = find_mouse_input();
        
        if (path_str.empty()) 
            return -1;

        const char *dev = path_str.c_str();
        int fd = open(dev, O_RDONLY | O_NONBLOCK);

        return fd;
    }

    void close_mouse(int fd)
    {
        close(fd);
    }

    std::string find_mouse_input()
    {
        const char *directory = "/dev/input/by-id/";
        DIR *dir = opendir(directory);

        if (dir == nullptr)
        {
            // Se falhar no by-id, tenta diretório raiz (fallback)
            directory = "/dev/input/";
            dir = opendir(directory);
             if (dir == nullptr) {
                std::cerr << "Erro crítico: Input folder not found." << std::endl;
                return "";
             }
        }

        struct dirent* entry;
        std::string mouse_path = "";

        while ((entry = readdir(dir)) != nullptr)
        {
            // Procura "event-mouse" (by-id) ou apenas "event" (fallback genérico)
            if (strstr(entry->d_name, "event-mouse") || strstr(entry->d_name, "event"))
            {
                // Ignora keyboard se cair no fallback
                if (strstr(entry->d_name, "kbd")) continue; 

                mouse_path = std::string(directory) + std::string(entry->d_name);
                // Se achou um com "mouse" no nome, prioridade total e sai
                if (strstr(entry->d_name, "mouse")) break;
            }
        }

        closedir(dir);
        return mouse_path;
    }
#endif





int main(int argc, char *argv[])
{
    // incialização de rand
    srand(time(NULL));

    // dados do vetor mãe
    Figura *ptr[MAX_OBJS];
    int size = 0;

    // teste de sudo
    int fd = open_mouse();
    if (fd == -1)
    {

        std::cerr << "Rode o programa com: sudo ./main" << std::endl;
        return 1;
    }

    short int end = 0, m_output = 0;

    // main loop do jogo
    while (!end)
    {
        m_output = detect_mouse(fd);
        if (m_output)
        {
            if ((rand() % 2) % 2 == 0)
                ptr[size] = new Circulo;
            else
                ptr[size] = new Triangulo;
            size++;
            std::cout << size << std::endl;
        }

        for (int i = 0; i < size; i++)
        {
            ptr[i]->desenhar();
        }
        std::cout << std::endl;

        // controla o fps do programa (100000 == 100ms de atraso)
        global_sleep(100000);
    }
    
    close_mouse(fd);
}




