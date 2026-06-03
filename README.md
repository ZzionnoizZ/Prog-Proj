
# Programming project

## Group elements

Identify all group elements (numbers and names).

- up202507359 Cauã Barbosa
- up202508214 Olga Zubenko
- up202507287 Bruno Lourenço


## Accomplished tasks
Começamos por definir 3 funções auxiliares:
 - Recolher: recebe uma string no formato “12 3” e devolve um Point {12, 3} usado no translate;
 - dados: recebe uma string no formato “translate(12 3)” e devolve uma string que corresponde a “12 3”;
 - parse_element: recebe um pointer do tipo XMLElement no formato <polygon points="75,75 75,125 125,125" fill="blue" transform-origin="100 100" transform="rotate(180)"/> e que retorna um pointer do tipo SVGElement;

Para além disso, criamos um map, chamado element_map, cuja chave é uma string e o valor é um pointer do tipo XMLElement.
Na função readSVG implementamos um ciclo for que percorre todos os elementos da raiz do ficheiro. Cada elemento percorrido é processado pela função parse_element que analisa e extrai as propriedades geométricas e visuais para instanciar as respetivas classes de figuras. Após essa análise, caso o elemento processado exista, ele é adicionado ao vetor svg_elements. 

A função parse_element para além de processar classe de figuras simples também suporta estruturas de grupo. Caso o elemento a ser processado seja um grupo, a função chama-se a si própria de forma recursiva para ler e instanciar as classes dos elementos do grupo. Assim como, a função permite a reutilização de elementos que quando possuem um id atribuído são guardados no element_map. Quando um elemento com a tag <use> é processado, percorremos o mapa para verificar se existe uma figura com o id igual à referência do elemento, no caso de existir o elemento atual passa a ter as características visuais e geométricas do elemento guardado no mapa através de uma recursão da função parse_element. Por fim, caso existam transformações a serem feitas, a função parse_element lê a transformação a ser feita e chama a função correspondente à transformação da classe do elemento processado, recorrendo às funções auxiliares Recolher e dados.