# projeto-cg-bcc

## Todo list

Projeção em Perspectiva

- COP -> Center Of Projection.
- VPN -> View Plane Normal.
- SCN -> Sistema de Coordenadas Normalizadas.

## Algoritmo para a projeção perspectiva.

- ~~Definir COP.~~
- ~~Translade COP para a origem do mundo.~~
  - ~~Transalação de todos os objetos do mundo.~~
- ~~Determine VPN. (Vetor Normal ao Plano de Projeção)~~
  - ~~Decomponha o vetor e determine os ângulos de VPN em torno de X e em torno de Y.~~
- ~~Rotacione o mundo em torno de X e de Y alinhando VPN com Z.~~
- ~~Projete os pontos pontos Xp e Yp usando a [matriz de perspectiva.](https://moodle.utfpr.edu.br/pluginfile.php/2759771/mod_page/content/3/CG%20-%20Aula15%20-%20Proje%C3%A7%C3%B5es%203D%20em%202D.pdf)~~
- ~~Normalize para gerar o SCN.~~
- ~~Faça o clipping.~~
- ~~Faça a transformada de viewport.~~
- ~~Desenhe.~~
- Implemetar UI.
  - ~~Movimento.~~
  - ~~Camera.~~
  - ~~Zoom.~~
    - Implementado, mas não funcional
  - Escalar.
- Testes.
  - Casos de uso.
    - Projeção Ortogonal (Não tenho certeza dos valores esperados)..
    - Projeção Prio.erspectiva (Não tenho certeza dos valores esperados).
  - Teste Unitá
    - Normalização Ortogonal (Reformulando contas).
    - Transformação da Viewport (Questionando necessidade).
    - Translação (Rafael).
    - Escala (Murilo).
    - Rotação do Mundo (Guilherme).
    - Rotação do Objeto. (Ricky)
  - E2E
    - Movimento.
    - Camera.
    - Zoom.

# Cenário de Testes

A = (3, 3 , 4)
B = (7, 3, 7)
C = (1, 3, 1)

P: Plano(A, B, C)

CoP = (0, 0, 0) -> E

v = (2 0 3) -> Vetor (CA)
u = (4 0 3) -> Vetor (AB)
w = (0, 6, 0) -> v ⊗ u (aka vetor normal ao plano)

D = (5, 5, 5) -> Point
F = (3, 3, 3) -> Result

// Piramide Triangular
G = (-2, 4, 0)
J = (-4, 4, 0)
I = (-4, 6, 0)
H = (-3, 5, 2) -> Top
//-----------------

# Descobertas

No arquivo .obj a linha f, referente as faces
segue o formato index_do_vertice1/index_da_textura1 index_do_vertice2/index_da_textura2 index_do_vertice3/index_da_textura3 de forma a formar um triangulo. Sabendo disso, podemos montar as arestas pelos indexs que formam os triangulos das faces.
