
#MALLOC

##Malloc

Malloc range ses multiples appelle en les divisant en trois categories,
tiny, small et large

DEFINITION DES PAGES DE MEMOIRE

- next : les pages sont des listes chainees
- size : taille totale de la page
- count	: Nombre de blocs
- blocksize : taille des espaces d'allocations a l'interieur de la page
- blocksinfo... : suite de la taille utilisée dans les blocs
- blocks... : les allocations elles meme
