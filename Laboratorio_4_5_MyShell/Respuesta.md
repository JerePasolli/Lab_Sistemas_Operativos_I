### ¿Dónde se encuentran los pipes en el filesystem, qué atributos tienen?
Los pipes no se encuentran en el filesystem que se encuentran los demás binarios, ya que se encuentra en otro filesystem "propio" virtual. Este filesystem virtual se llama PipeFS. Se encuentra montado en el kernel. A diferencia de otros filesystems que están montados bajo "/", este se encuentra montado en "pipe", es decir que tiene su propio directorio root. La entrada a este fylesistem es la llamada al sistema "pipe()". Este filesystem no puede ser visto por los usuarios, y es un sisteama de archivos en memoria.