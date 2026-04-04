## SSR (Server-Side Rendering)

El contenido HTML de la página se genera en el servidor cada vez que el usuario hace una petición.
El servidor envía la página ya renderizada al navegador.
Ventajas: mejor SEO, contenido visible rápidamente.
Ejemplo: aplicaciones con frameworks como Next.js (en modo SSR) o páginas tradicionales con Express y plantillas.

## CSR (Client-Side Rendering)

El servidor envía un HTML básico y un archivo JavaScript.
El navegador descarga el JS y genera el contenido dinámicamente en el cliente.
Ventajas: experiencia de usuario más interactiva, menos carga en el servidor.
Ejemplo: aplicaciones SPA hechas con React, Vue o Angular.

## SSG (Static Site Generation)

El contenido HTML se genera en tiempo de build (antes de que el usuario lo solicite).
El servidor entrega archivos estáticos ya listos.
Ventajas: carga ultra rápida, muy seguro, ideal para contenido que no cambia seguido.
Ejemplo: sitios hechos con Gatsby, Hugo, Next.js (en modo SSG).
Resumen:

SSR: Renderiza en el servidor en cada petición.
CSR: Renderiza en el cliente usando JS.
SSG: Renderiza una vez en build y sirve archivos estáticos.