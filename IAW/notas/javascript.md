## Javascript
Javscript es un lenguaje single threaded. Es decir, realiza una tare a la vez.
Las operaciones asíncronas como fetch() devuelven promesas:
	promesa.then(...).cath(...)

Se pueden concatenar then, cada then procesa el dato recibido del then anterior

	tareaAsincrona()
	.then(...)		
	.then(...)
	.then(...)
	.catch(...)

Ejemplo:
	fetch("...")
	.then(r => r.json())
	.then(data => {return data.length;})
	.then(len => console.log(len));

### Creación de promesas:
	const promesa = new Promise(
		function(resolve, reject) {
		   // codigo que produce algún resultado
		}
	)
El parámetro de las funciones es sólo un dato referencial:
resolve(10)
resolve("ok")
