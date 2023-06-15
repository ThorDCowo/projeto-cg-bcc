# projeto-cg-bcc

## Todo list

Projeção em Perspectiva

- COP -> Center Of Projection.
- VPN -> View Plane Normal.
- SCN -> Sistema de Coordenadas Normalizadas.

## Algoritmo para a projeção perspectiva.

- Definir COP.
- Translade COP para a origem do mundo.
  - Transalação de todos os objetos do mundo.
- Determine VPN. (Vetor Normal ao Plano de Projeção)
  - Decomponha o vetor e determine os ângulos de VPN em torno de X e em torno de Y.
- Rotacione o mundo em torno de X e de Y alinhando VPN com Z.
- Projete os pontos pontos Xp e Yp usando a [matriz de perspectiva.](https://moodle.utfpr.edu.br/pluginfile.php/2759771/mod_page/content/3/CG%20-%20Aula15%20-%20Proje%C3%A7%C3%B5es%203D%20em%202D.pdf)
- ~~Normalize para gerar o SCN.~~
- ~~Faça o clipping.~~
- ~~Faça a transformada de viewport.~~
- ~~Desenhe.~~
