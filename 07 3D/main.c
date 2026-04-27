#include <SL.h>
    
int main(int argc, char* argv[])
{
	SL_init();
	
    slWindow* win = slWindow_new("SL", 800,600);
    
    slInput* in = slInput_init();
    
    slShader* shader = slShader_init("mat");
    
    slTexture* texture1 = slTexture_init("container.jpg");
    slTexture* texture2 = slTexture_init("awesomeface.png");
    
    float vertices[] = {

-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

0.5f, -0.5f, -0.5f, 1.0f, 0.0f,

0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,

-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

0.5f, -0.5f, 0.5f, 1.0f, 0.0f,

0.5f, 0.5f, 0.5f, 1.0f, 1.0f,

0.5f, 0.5f, 0.5f, 1.0f, 1.0f,

-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,

-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

0.5f, -0.5f, -0.5f, 1.0f, 1.0f,

0.5f, -0.5f, 0.5f, 1.0f, 0.0f,

0.5f, -0.5f, 0.5f, 1.0f, 0.0f,

-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,

0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,

-0.5f, 0.5f, -0.5f, 0.0f, 1.0f

};
      
     unsigned int indices[] = {
                                   0, 1, 2,
                                   2, 3, 0
      };
    
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
(void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    
    // unbind EBO never before VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    // model view projection
    mat4 model;
      glm_mat4_identity(model);
      glm_rotate(model, glm_rad(-55.0f),
(vec3){1.f, 0.f, 0.f});
      
      mat4 view;
      glm_mat4_identity(view);
      glm_translate(view, (vec3){0.f, 0.f, -3.f});
      
      mat4 projection;
      glm_perspective(glm_rad(45.f), 800.f / 600.f, 0.1f, 100.f, projection);
      
      int modelLoc, viewLoc, projectionLoc;

    // render loop
    // -----------
    while (slWindow_getStatus(win))
    {
        slInput_update(in);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        slShader_use(shader);
        
        slTexture_use(texture1, 0);
        slTexture_use(texture2, 1);
        
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        
        glm_rotate(model, (float)SDL_GetTicks() / 1000000.f * glm_rad(50.f),
(vec3){0.5f, 1.0f, 0.0f});
        
        modelLoc = glGetUniformLocation(slShader_get(shader), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, *model);
        
        viewLoc = glGetUniformLocation(slShader_get(shader), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, *view);
        
        projectionLoc = glGetUniformLocation(slShader_get(shader), "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, *projection);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glBindVertexArray(0); // no need to unbind it every time 

        slWindow_draw(win);
    }
    
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    
    slTexture_free(&texture2);
    slTexture_free(&texture1);
    slShader_free(&shader);
    slInput_free(in);
    slWindow_free(win);
    SL_quit();
    
    return 0;
}
