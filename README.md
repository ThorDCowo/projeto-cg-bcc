# projeto-cg-bcc

## Todo list

Implementar o clipping 2D em seu sistema de visualização; 
- Algoritmo de **Cohen-Sutherland**;
    - **Region Code** [Veja o slide 14](https://moodle.utfpr.edu.br/pluginfile.php/2741976/mod_page/content/3/CG%20-%20Aula10%20-%20Clipping.pdf);
        - ~~se o y de P1 é maior que y da borda superior: RC[1] = 1~~;
        - ~~se o y de P1 é maior que y da borda inferior: RC[2] = 1~~;
        - ~~se o x de P1 é maior que x da borda direita:  RC[3] = 1~~;
        - ~~se o x de P1 é menor que x da borda esquerda: RC[4] = 1~~;
    - **Clipping** [Slides](https://moodle.utfpr.edu.br/pluginfile.php/2741976/mod_page/content/3/CG%20-%20Aula10%20-%20Clipping.pdf);
        - Vericifar qual dos 3 casos se trata AND lógico:
            - ~~Totalmente fora~~ -> Remover da Coordenada de Desenho;
            - ~~Totalmente dentro -> Nada a fazer~~;
            - ~~Parcialmente dentro~~ -> Utilizar a equação da reta pra calcular o novo ponto;
    - **Equação da Reta** para cada borda;
        - Esquerda: Y = m * (Xe - X1) + Y1;
        - Direita:  Y = m * (Xd - X1) + Y1;
        - Topo:     X = X1 + 1/m * (Yt - Y1);
        - Base:     X = X1 + 1/m * (Yf - Y1);
- ~~Na área de desenho, desenhe uma moldura interna para representar sua viewport~~;
- Modifique a window usando as transformações geométricas para ver o efeito em sua área de desenho;