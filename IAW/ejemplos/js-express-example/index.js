// Imports
const express = require('express');
const path = require('path');
const { faker } = require('@faker-js/faker');

// Properties
const app = express();
const PORT = process.env.PORT || 3000;

// Set resources path
app.use(express.static(path.join(__dirname, 'public')));

// Routes
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

// Start server
app.listen(PORT, () => {
	console.log(`Servidor escuchando en http://localhost:${PORT}`);
});

app.get("/saludar", (req, res) => {
	const { nombre } = req.query;

	if (!nombre) {
		return res.status(400).send("Debes enviar el query param nombre");
	}

	res.send(`<h1>Hola, ${nombre}</h1>`);
});

app.get("/empleado-ficticio", (req, res) => {
	res.json(generateFakeData());
});

app.get("/empleados-ficticios", (req, res) => {
	const cantidadRaw = req.query.cantidad ??  req.query.x;
	const cantidad = Number(cantidadRaw);

	if (!Number.isInteger(cantidad) || cantidad <= 0) {
		return res.status(400).json({
			error: 'Debes enviar un número entero positivo en el query param'
		});
	}

	if (cantidad > 1000) {
		return res.status(400).json({
			error: "La cantidad maxima permitida es 1000"
		});
	}

	const empleados = Array.from({ length: cantidad }, () => generateFakeData());
	res.json(empleados);

});

// Functions
function generateFakeData() {
    return {
        id: faker.string.uuid(),
		nombre: faker.person.fullName(),
		email: faker.internet.email(),
		telefono: faker.phone.number(),
		puesto: faker.person.jobTitle(),
		departamento: faker.commerce.department(),
		salario: Number(faker.finance.amount({ min: 30000, max: 120000, dec: 0 }))
    };
}
