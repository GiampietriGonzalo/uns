# On-Demand Revalidation con Tags - Guía Completa

Te explicaré esta estrategia de forma clara y progresiva con ejemplos prácticos.

---

## **¿Qué es On-Demand Revalidation?**

Es un mecanismo que te permite **invalidar (limpiar) el caché de contenido estático en el momento exacto que lo necesites**, sin esperar a un intervalo de tiempo.

**Analogía**: Imagina que tienes un periódico impreso en tu casa. En lugar de imprimir uno nuevo cada hora o cada día, solo lo reimprime cuando sucede una noticia importante. Eso es on-demand revalidation.

---

## **¿Qué son los Tags?**

Los **tags** son **etiquetas o identificadores** que asignas a los datos obtenidos en el fetch. Sirven para agrupar múltiples rutas/páginas que usan los mismos datos.

**Ejemplo visual**:
```
Tu sitio web de blog
│
├─ /blog/post-1
├─ /blog/post-2         } Todos usan datos de la API
├─ /blog/post-3         } y están etiquetados como 'posts'
└─ /blog              }
```

Cuando revalidas el tag `'posts'`, **todas esas páginas se regeneran**.

---

## **Paso 1: Etiquetar los Datos en Fetch**

Cuando haces un fetch en una página/componente, agregas un tag:

```javascript
// app/blog/page.tsx
export default async function BlogPage() {
  const res = await fetch('https://api.ejemplo.com/posts', {
    next: { tags: ['posts'] }  // ← Etiqueta los datos
  })
  const posts = await res.json()
  
  return (
    <div>
      {posts.map(post => (
        <article key={post.id}>{post.title}</article>
      ))}
    </div>
  )
}
```

**¿Qué pasa?**
- La página se **renderiza estáticamente** durante el build
- Los datos se **cachean con el tag 'posts'**
- Mientras el caché esté válido, todos reciben esta página estática

---

## **Paso 2: Crear un Endpoint API para Revalidar**

Creas una ruta en tu API que recibe una solicitud y limpia el caché:

```javascript
// app/api/revalidate/route.ts
import { revalidateTag } from 'next/cache';
import { NextRequest, NextResponse } from 'next/server';

export async function POST(request: NextRequest) {
  // 1. Obtener el tag del body de la solicitud
  const { tag } = await request.json();
  
  // 2. Validar que existe un token secreto (seguridad)
  const secret = request.headers.get('x-api-secret');
  if (secret !== process.env.REVALIDATE_SECRET) {
    return NextResponse.json(
      { error: 'Unauthorized' },
      { status: 401 }
    );
  }
  
  // 3. Revalidar el tag
  revalidateTag(tag);
  
  // 4. Responder al cliente
  return NextResponse.json(
    { 
      revalidated: true,
      tag: tag,
      timestamp: new Date().toISOString()
    },
    { status: 200 }
  );
}
```

---

## **Paso 3: Disparar la Revalidación Desde Tu Backend**

Cuando algo cambia en tu base de datos (nuevo post, actualización, etc.), **llamas al endpoint**:

```javascript
// En tu backend o servicio de base de datos
async function publishNewPost(postData) {
  // 1. Guardar en base de datos
  const newPost = await db.posts.create(postData);
  
  // 2. Limpiar el caché de Next.js
  await fetch('https://tudominio.com/api/revalidate', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
      'x-api-secret': process.env.REVALIDATE_SECRET
    },
    body: JSON.stringify({ tag: 'posts' })
  });
  
  return newPost;
}
```

---

## **Flujo Completo: Ejemplo Real de Blog**

### **Escenario: Blog con artículos**

**1. Construcción (Build Time)**
```
npm run build
↓
Next.js renderiza:
  /blog → GET /api/posts → Tag: 'posts' ✓
  /blog/1 → GET /api/posts/1 → Tag: 'post-1' ✓
  /blog/2 → GET /api/posts/2 → Tag: 'post-2' ✓
  
Resultado: Páginas estáticas en caché
```

**2. Usuario escribe un artículo**
```
Usuario → Panel admin → Botón "Publicar"
                         ↓
                    Guardar en BD
                         ↓
                    POST /api/revalidate
                    { tag: 'posts' }
```

**3. Revalidación (On-Demand)**
```
revalidateTag('posts')
↓
Limpia caché de:
  - /blog
  - /blog/1
  - /blog/2
  - Cualquier página con tag 'posts'
↓
Próxima visita: Se regeneran esas páginas
```

**4. Usuario visita el blog**
```
GET /blog
↓
Next.js detecta que el caché fue limpiado
↓
Ejecuta el fetch nuevamente
↓
Obtiene datos frescos con el nuevo post
↓
Sirve la página actualizada
```

---

## **Tags Múltiples: Granularidad**

Puedes usar **múltiples tags** para mayor control:

```javascript
// app/blog/[id]/page.tsx
export default async function PostPage({ params }) {
  const res = await fetch(`https://api.ejemplo.com/posts/${params.id}`, {
    next: { tags: ['posts', `post-${params.id}`, 'blog-content'] }
  })
  const post = await res.json()
  
  return <article>{post.content}</article>
}
```

Luego puedes revalidar **selectivamente**:

```javascript
// Opción 1: Regenerar todos los posts
revalidateTag('posts');

// Opción 2: Regenerar solo un post específico
revalidateTag('post-1');

// Opción 3: Regenerar todo el contenido del blog
revalidateTag('blog-content');
```

---

## **Caso de Uso: E-commerce**

```javascript
// app/productos/page.tsx
export default async function ProductsPage() {
  const res = await fetch('https://api.tienda.com/products', {
    next: { tags: ['productos', 'inventario'] }
  })
  const products = await res.json()
  return <div>{/* renderizar */}</div>
}

// Cuando el admin actualiza el inventario:
// POST /api/revalidate
// { tag: 'inventario' }
// ↓ Se regenera la página de productos

// Cuando se agrega un nuevo producto:
// POST /api/revalidate
// { tag: 'productos' }
// ↓ Se regenera la página de productos
```

---

## **Ventajas vs Desventajas**

### ✅ **Ventajas**
- **Rapidez**: Páginas estáticas, pero actualizadas cuando es necesario
- **Control total**: Revalidar exactamente cuando quieras
- **Escalabilidad**: No depende de intervalos de tiempo
- **Granularidad**: Con tags, revalidas solo lo que necesitas

### ⚠️ **Desventajas**
- **Complejidad**: Requiere configurar un endpoint API adicional
- **Dependencia de webhooks**: Necesitas notificar a Next.js desde tu backend
- **Seguridad**: Debes proteger el endpoint con tokens secretos

---

## **Comparación con Otras Estrategias**

```
Estrategia          Actualización          Complejidad    Caso de Uso
─────────────────────────────────────────────────────────────────────
Static              En build (nunca)       ⭐            Documentación
ISR                 Cada X segundos        ⭐⭐          Noticias
On-Demand           Bajo demanda           ⭐⭐⭐        Blogs, e-commerce
Dynamic             Cada request           ⭐             Datos en tiempo real
```

---

## **Resumen**

| Concepto | Explicación |
|----------|------------|
| **Tag** | Etiqueta que identificas en tus datos para poder revalidarlos después |
| **next: { tags: ['posts'] }** | Asignas el tag al hacer fetch |
| **revalidateTag('posts')** | Limpias el caché de ese tag |
| **Endpoint /api/revalidate** | Ruta que recibe solicitudes para limpiar caché |
| **On-Demand** | Revalidar en el momento exacto que lo necesitas |

**On-Demand Revalidation es la estrategia perfecta cuando tienes contenido que cambia de forma impredecible pero que no necesita ser actualizado en tiempo real.**
