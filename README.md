# Los-Simpsons-Aleatorios

A todos nos pasa, llegamos cansados de la escuela o trabajo, pedimos algo de cenar y nos preparamos para ver otro episodio mas de nuestra familia amarilla favorita, sin embargo, hay tantas temporadas y episodios que simplemente no sabemos cual elegir.

Ya no mas, con este "randomizer" de episodios de los simpsons solo tendras que seleccionar las especificaciones de tu consulta y obtendras un lista de capitulos con
esas caracteristicas, reduciendo la carga de tener que seleccionar entre cientos y cientos de estos.

# ¿Como se creo?

El programa utiliza una base de datos embebida (SQLite) que cree con todos los capitulos de Los Simpsons, de la temporada 1 a la temporada 34, esta cuenta con el
titulo del capitulo, una breve descripcion, la temporada a la que pertenece y si este es un episodio de halloween o no.

# ¿Como funciona?

Por defecto el programa comenzara con un consulta basica, la cual buscara todo tipo de capitulos y solo mostrara una recomendacion.

El programa se basa principalmente en tres menus

# Menu principal

Al iniciar tendremos cuatro opciones:

Realizar consulta: Nos pasara directamente al menu de consultas

Solo mostrar episodios de halloween: Nos pasara a un menu donde podremos seleccionar si queremos que la consulta solo nos muestre capitulos de halloween (legendarios para todo fanatico de Los Simpsons), o todo tipo de capitulos

Seleccionar numero de recomendaciones: Nos pasara a un menu donde podremos seleccionar cuantas recomendaciones queremos que se nos muestre en una misma consulta,
podremos elegir entre una y diez

Salir del programa: Cierra el programa

# Menu consulta

Tendremos tres tipos de consultas en el programa:

Consulta por temporada: Aqui buscaremos capitulos exclusivamente en la temporada que seleccionemos

Consulta por rango: Aqui buscaremos capitulos en el rango de temporadas que hemos seleccionado

Consulta aleatoria: Aqui buscaremos capitulo en todas las temporadas

# Menu reinicio

Tendremos tres opciones al terminar la consulta:

Reinicio rapido: Nos permitira realizar rapidamente otra consulta con los mismos parametros y el tipo de consulta que ya hemos seleccionado

Reinicio completo: Reestablecera todos los parametros nuestra consulta a los parametros por defecto (todo tipo de episodios y solo una recomendacion) y posteriormente nos regresara al menu principal

Regresar al menu principal: Nos regresara al menu principal sin reestablecer ningun parametro de nuestra consulta (ej. Si la consulta anterior buscaba tres recomendaciones, entonces la siguiente consulta tambien lo hara a menos que modifiquemos esto manualmente)


