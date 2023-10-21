#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "utility.h" 

// Inisialisasi kecepatan jarum detik, menit, dan jam
float velocitySecondPointer = -6.0f / 2;
float velocityMinutePointer = -0.1f / 2;
float velocityHourPointer = -0.0083333f / 2;


// Nilai awal sudut jarum detik, menit, dan jam
float currentSecondPointer = 270.0f;
float currentMinutePointer = 270.0f;
float currentHourPointer = 270.0f;

float currentTime = 0.0f;
float lastTime = 0.0f;
float deltaTime = 0.0f;

float speed = 1.0f; // Kecepatan awal

unsigned int program;

GLint color1Loc, color2Loc, color3Loc;

// Warna untuk jarum-jarum jam
float color1[] = { 1.0, 0.0, 0.0, 1.0 }; // Merah
float color2[] = { 0.0, 1.0, 0.0, 1.0 }; // Hijau
float color3[] = { 0.0, 0.0, 1.0, 1.0 }; // Biru

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        //Tombol C untuk mengatur ulang waktu 
        float jam, menit, detik;
        std::cout << "Atur ulang waktu" << std::endl;
        std::cout << "Jam : ";
        std::cin >> jam;

        std::cout << "Menit : ";
        std::cin >> menit;

        std::cout << "Detik : ";
        std::cin >> detik;

        float jamBaru = jam * 3600;
        float menitBaru = menit * 60;
        float detikBaru = detik;

        glfwSetTime(jamBaru + menitBaru + detikBaru);
    }
    
    else if (key == GLFW_KEY_W && action == GLFW_PRESS){
        // Tombol 'W' ditekan, tambahkan 1 menit
        glfwSetTime(currentTime + 60);
        std::cout << "Added 1 minute" << std::endl;
    }
    else if (key == GLFW_KEY_Q && action == GLFW_PRESS){
        // Tombol 'Q' ditekan, kurangi 1 menit
        glfwSetTime(currentTime - 60);
        std::cout << "Subtracted 1 minute" << std::endl;
    }
    else if (key == GLFW_KEY_E && action == GLFW_PRESS){
        // Tombol 'E' ditekan, tambahkan 1 jam
        glfwSetTime(currentTime + 3600);
        std::cout << "Added 1 hour" << std::endl;
    }
    else if (key == GLFW_KEY_R && action == GLFW_PRESS){
        // Tombol 'R' ditekan, kurangi 1 jam
        glfwSetTime(currentTime - 3600);
        std::cout << "Subtracted 1 hour" << std::endl;
    }
    else if (key == GLFW_KEY_P && action == GLFW_PRESS){
        // Tombol 'P' ditekan, percepat pergerakan waktu
        speed += 1.0f;
        std::cout << "Increased speed by " << ceil(speed) << " times" << std::endl;
    }
    else if (key == GLFW_KEY_O && action == GLFW_PRESS){
        // Tombol 'O' ditekan, reset kecepatan ke nilai awal
        speed = 1.0f;
        std::cout << "Reset speed to normal" << std::endl;
    }
    else if (key == GLFW_KEY_Z && action == GLFW_PRESS){
        // Tombol 'Z' ditekan, ubah warna jarum-jarum jam secara acak
        std::cout << "Colors changed" << std::endl;
        for (int i = 0; i < 3; i++){
            color1[i] = static_cast<float>(rand()) / RAND_MAX;
            color2[i] = static_cast<float>(rand()) / RAND_MAX;
            color3[i] = static_cast<float>(rand()) / RAND_MAX;
        }
        // Update warna di shader program
        glUniform4f(color1Loc, color1[0], color1[1], color1[2], color1[3]);
        glUniform4f(color2Loc, color2[0], color2[1], color2[2], color2[3]);
        glUniform4f(color3Loc, color3[0], color3[1], color3[2], color3[3]);
    }
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 740, "Skuy Grafika RGBs Clock", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Mengatur fungsi callback untuk input keyboard
    glfwSetKeyCallback(window, keyCallback);

    GLenum err = glewInit();

    // Definisi vertex data
    float vertices[] = {
        1.0f, 1.0f,
        -1.0f, 1.0f,
        -1.0f, -1.0f,
        1.0f, -1.0f
    };

    unsigned int indexArr[] = {
        0, 1, 2, 0, 2, 3
    };

    unsigned int vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indexArr, GL_STATIC_DRAW);

    string vertexString = readFile("vertex.vert");
    string fragmentString = readFile("fragment.frag");

    const char* vertexChar = vertexString.c_str();
    const char* fragmentChar = fragmentString.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexChar, NULL);
    glShaderSource(fragmentShader, 1, &fragmentChar, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glUseProgram(program);

    GLint currentSecondPointerLoc = glGetUniformLocation(program, "currentSecondPointer");
    GLint currentMinutePointerLoc = glGetUniformLocation(program, "currentMinutePointer");
    GLint currentHourPointerLoc = glGetUniformLocation(program, "currentHourPointer");

    GLint color1Loc = glGetUniformLocation(program, "color1");
    GLint color2Loc = glGetUniformLocation(program, "color2");
    GLint color3Loc = glGetUniformLocation(program, "color3");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        deltaTime = (currentTime - lastTime) * speed;
        lastTime = currentTime;

        // Perbarui sudut jarum-jarum jam sesuai waktu
        currentSecondPointer += (deltaTime * velocitySecondPointer);
        currentMinutePointer += (deltaTime * velocityMinutePointer);
        currentHourPointer += (deltaTime * velocityHourPointer);

        // Update nilai sudut jarum-jarum jam dalam bentuk radian
        glUniform1f(currentSecondPointerLoc, currentSecondPointer * 3.14159265f / 180.0f);
        glUniform1f(currentMinutePointerLoc, currentMinutePointer * 3.14159265f / 180.0f);
        glUniform1f(currentHourPointerLoc, currentHourPointer * 3.14159265f / 180.0f);

        // Update warna jarum-jarum jam di shader program
        glUniform4f(color1Loc, color1[0], color1[1], color1[2], color1[3]);
        glUniform4f(color2Loc, color2[0], color2[1], color2[2], color2[3]);
        glUniform4f(color3Loc, color3[0], color3[1], color3[2], color3[3]);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Gambar elemen-elemen dengan triangulasi
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
