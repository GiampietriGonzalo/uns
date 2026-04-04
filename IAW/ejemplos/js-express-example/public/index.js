
const form = document.getElementById("form-empleados");
const statusEl = document.getElementById("status");
const bodyEl = document.getElementById("empleados-body");

function formatMoney(value) {
  return new Intl.NumberFormat("es-AR", {
    style: "currency",
    currency: "USD",
    maximumFractionDigits: 0,
  }).format(value);
}

function renderRows(empleados) {
  bodyEl.innerHTML = empleados
    .map(
      (empleado) => `
        <tr>
          <td><code>${empleado.id}</code></td>
          <td>${empleado.nombre}</td>
          <td>${empleado.email}</td>
          <td>${empleado.telefono}</td>
          <td>${empleado.puesto}</td>
          <td>${empleado.departamento}</td>
          <td>${formatMoney(empleado.salario)}</td>
        </tr>
      `
    )
    .join("");
}

async function cargarEmpleados(cantidad) {
  statusEl.classList.remove("error");
  statusEl.textContent = "Cargando empleados...";

  try {
    const response = await fetch(`/empleados-ficticios?cantidad=${cantidad}`);
    const data = await response.json();

    if (!response.ok) {
      throw new Error(data.error || "No se pudo obtener la lista de empleados");
    }

    renderRows(data);
    statusEl.textContent = `Se cargaron ${data.length} empleados.`;
  } catch (error) {
    bodyEl.innerHTML = "";
    statusEl.classList.add("error");
    statusEl.textContent = error.message;
  }
}

form.addEventListener("submit", (event) => {
  event.preventDefault();
  const cantidad = Number(new FormData(form).get("cantidad"));
  cargarEmpleados(cantidad);
});

cargarEmpleados(10);
