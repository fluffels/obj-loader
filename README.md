obj-loader
==========

Simple partial implementation of the OBJ specification.

How To
------

Follow the following steps:

1. Include the OBJMesh headers

```C++
#include "Mesh.h"
#include "OBJMesh.h"
```

2. Create a mesh object.

```C++
Mesh* m = new OBJMesh("/path/to/objfile");
```

3. In your display function, render the mesh.

```C++
m->draw();
```

4. Don't forget to clean up as you're shutting down the program.

```C++
delete m;
```


Notes
-----

The Mesh object expects the existence of certain vertex attributes:

```glsl
vec3 position;
vec3 normal;
vec3 texel;
```

