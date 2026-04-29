# Buyer App — MateandoAndo

## Propósito

La **Buyer App** es la aplicación central de la experiencia de compra dentro del marketplace MateandoAndo. Está diseñada para que compradores particulares puedan explorar el catálogo de productos artesanales de mate y artículos relacionados, gestionar su perfil y direcciones de envío, mantener un carrito de compras activo, realizar el proceso de checkout y hacer seguimiento de sus pedidos.

En términos de arquitectura, actúa como el punto de entrada del comprador al ecosistema y como intermediaria en la comunicación con el resto de las aplicaciones del sistema (Seller App, Payments App y Shipping App).

---

## Rol en el flujo principal de uso

La Buyer App participa activamente en los pasos 2 y 5 del flujo principal:

1. **Paso 2 — Compra:** El comprador busca un producto (por ejemplo, un mate imperial o una bombilla de alpaca), lo agrega al carrito y dispara el proceso de checkout desde la Buyer App.
2. **Paso 3 — Pago:** El pago se delega a la Payments App. La Buyer App recibe la notificación del resultado (aprobado o rechazado) a través de un webhook interno.
3. **Paso 5 — Seguimiento:** Una vez despachado el paquete, el comprador puede rastrear su pedido en tiempo real desde la Buyer App, consumiendo la Shipping App.

---

## Datos que mantiene

La Buyer App administra tres tablas propias en su base de datos:

### `buyers` — Compradores

| Campo         | Tipo      | Descripción                                           |
|---------------|-----------|-------------------------------------------------------|
| id_buyer      | UUID (PK) | Identificador interno del comprador                   |
| clerk_user_id | UUID      | ID único del comprador provisto por Clerk             |
| first_name    | TEXT      | Nombre del comprador                                  |
| last_name     | TEXT      | Apellido del comprador                                |
| phone         | TEXT      | Teléfono de contacto                                  |
| status        | ENUM      | Estado de la cuenta: `ACTIVO` o `SUSPENDIDO`          |
| created_at    | TIMESTAMP | Fecha de creación del perfil                          |
| updated_at    | TIMESTAMP | Última fecha de modificación del perfil               |

### `addresses` — Direcciones de envío

| Campo      | Tipo      | Descripción                                              |
|------------|-----------|----------------------------------------------------------|
| id_address | UUID (PK) | Identificador interno de la dirección                    |
| id_buyer   | UUID (FK) | Comprador dueño de la dirección                          |
| alias      | TEXT      | Nombre descriptivo ("casa", "trabajo", etc.)             |
| street     | TEXT      | Calle y número                                           |
| floor_apt  | TEXT      | Piso y departamento (opcional)                           |
| city       | TEXT      | Ciudad                                                   |
| province   | TEXT      | Provincia                                                |
| zip_code   | TEXT      | Código postal                                            |
| is_default | BOOLEAN   | Indica si es la dirección predeterminada del comprador   |

### `carts` — Carritos de compras

| Campo      | Tipo      | Descripción                                                              |
|------------|-----------|--------------------------------------------------------------------------|
| id_cart    | UUID (PK) | Identificador interno del carrito                                        |
| id_buyer   | UUID (FK) | Comprador dueño del carrito (un solo carrito activo por comprador)       |
| created_at | TIMESTAMP | Fecha de creación del carrito                                            |
| updated_at | TIMESTAMP | Última fecha de modificación del carrito                                 |

---

## APIs que expone

Los siguientes endpoints son provistos por la Buyer App para ser consumidos por otras aplicaciones del sistema:

### `PATCH /api/buyers/payment-notification`
**Consumidor:** Payments App  
Recibe la notificación de confirmación o rechazo de un pago procesado en Mercado Pago.

**Request:**
```json
{
  "id_purchase_order": "ord_456",
  "id_payment_operation": "txn_888",
  "status": "APROBADO",
  "payment_hash": "mercadopago_hash_abc123"
}
```
**Response:**
```json
{
  "id_purchase_order": "ord_456",
  "status": "APROBADO",
  "updated_at": "2026-04-18"
}
```

---

### `GET /api/customers/{id_user}`
**Consumidor:** Shipping App  
Devuelve los datos personales del comprador (nombre, apellido, teléfono) necesarios para armar la guía de envío.

**Response:**
```json
{
  "id_user": "user_clerk_99",
  "first_name": "Juan",
  "last_name": "Pérez",
  "phone": "+5492915551234",
  "email": "juan@example.com"
}
```

---

### `GET /api/buyers/{id_buyer}`
**Consumidor:** Seller App  
Permite validar la identidad de un comprador.

**Response:**
```json
{
  "id_buyer": "buyer_999",
  "first_name": "Juan",
  "last_name": "Pérez",
  "phone": "+5492915551234",
  "status": "active"
}
```

---

### `GET /api/cart`
**Consumidor:** Frontend interno de la Buyer App  
Devuelve la cabecera del carrito activo del comprador autenticado.

**Response:**
```json
{
  "id_cart": "cart_1",
  "id_buyer": "buyer_999",
  "created_at": "2026-04-18",
  "updated_at": "2026-04-18"
}
```

---

## APIs que consume

La Buyer App realiza llamadas a otras aplicaciones para obtener datos y accionar sobre ellas:

| App destino   | Endpoint                                        | Para qué                                                     |
|---------------|-------------------------------------------------|--------------------------------------------------------------|
| Seller App    | `GET /api/items`                                | Listar todos los productos del catálogo                      |
| Seller App    | `GET /api/categories`                           | Obtener todas las categorías disponibles                     |
| Seller App    | `GET /api/categories/{category_name}`           | Filtrar productos por categoría                              |
| Seller App    | `GET /api/categories/{category_name}/{id_item}` | Ver detalle de un producto específico                        |
| Seller App    | `GET /api/sellers`                              | Listar todos los vendedores                                  |
| Seller App    | `GET /api/sellers/{id_seller}`                  | Ver el perfil de un vendedor                                 |
| Seller App    | `POST /api/purchase-orders`                     | Confirmar el carrito y generar la orden de compra            |
| Seller App    | `POST /api/discounts`                           | Consultar productos con promoción activa                     |
| Shipping App  | `POST /api/shippings/estimate`                  | Obtener el costo de envío estimado durante el checkout       |
| Shipping App  | `GET /api/shippings/track/{id_package}`         | Rastrear el estado del paquete en tiempo real                |
| Payments App  | `PATCH /api/payments/transactions/{id}/cancelled` | Solicitar la cancelación de una compra antes del despacho  |

---

## Autenticación y roles

La Buyer App utiliza **Clerk** como servicio de autenticación. Cada comprador se identifica con un token JWT emitido por Clerk, del cual se extraen los siguientes claims:

| Claim           | Uso                                                                                                                          |
|-----------------|------------------------------------------------------------------------------------------------------------------------------|
| `sub`           | Clave principal del comprador. Se persiste como `clerk_user_id` en la tabla `buyers` y filtra todas las consultas propias.   |
| `email`         | Identificación del usuario. Se muestra en la UI, pero no se almacena en la base de datos.                                    |
| `metadata.role` | Autorización. Define qué endpoints puede consumir cada usuario según su rol.                                                 |

### Roles relevantes para la Buyer App

| Rol               | Acceso habilitado                                                                                        |
|-------------------|----------------------------------------------------------------------------------------------------------|
| `buyer`           | Acceso completo a la Buyer App, Payments App y seguimiento en Shipping App.                              |
| `admin-buyer`     | Gestión de compradores y consulta de reportes dentro de la Buyer App.                                    |
| `shipping`        | Rol de sistema que autoriza a Shipping App a consumir `GET /api/customers/{id_user}`.                    |
| `payments`        | Rol de sistema que autoriza a Payments App a invocar `PATCH /api/buyers/payment-notification`.           |

---

## Datos compartidos con otras apps

La Buyer App es la **fuente de verdad** del identificador del comprador (`id_buyer`). Las demás aplicaciones (Seller App y Payments App) almacenan este ID como referencia externa sin replicar el perfil completo.

| Dato              | Apps que lo referencian             | Estrategia                                                                 |
|-------------------|-------------------------------------|----------------------------------------------------------------------------|
| `clerk_user_id`   | Todas las apps                      | Cada app sincroniza al primer login vía webhook o carga diferida (lazy load). |
| `id_buyer`        | Buyer App (origen), Seller App, Payments App | Seller y Payments almacenan el ID como FK externa, sin replicar el perfil. |

---

## Resumen de responsabilidades

La Buyer App es la cara visible del marketplace para el comprador. Centraliza la experiencia de exploración, compra y seguimiento, y actúa como fuente de verdad del perfil del comprador. Su correcta integración con Seller App, Payments App y Shipping App es lo que permite que el flujo de compra funcione de punta a punta dentro de MateandoAndo.
