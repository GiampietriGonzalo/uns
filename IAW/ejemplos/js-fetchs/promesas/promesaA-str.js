// Creamos una promesa que a veces falla, a veces no.
const prometer = () =>{
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            // numero al azar entre 0 y 1
            if (Math.random() > 0.5) {
                resolve("exito");
            }
            reject("fracaso");
        }, 2000)
    });
}


console.log("Accion 1");
console.log("Pruebo una accion asincrona");
prometer()
    .then((value) => { return `${value} primera parte` })
    .then((value) => { return `${value} ==> segunda parte` })
    .then((value) => { return `${value} ==> tercera parte` })
    .then((value) => { console.log("Finalizada exitosamente:| "+value+"|");})
    .catch((value) => { console.log("Fallada :"+value);})



console.log("Accion 2");
console.log("Accion 3");
console.log("Accion 4");


/*
Resultado posible:

- Éxito: 
    Accion 1
    Pruebo una accion asincrona
    Accion 2
    Accion 3
    Accion 4
    Finalizada exitosamente:| exito primera parte ==> segunda parte ==> tercera parte|

- Fracaso:
    Accion 1
    Pruebo una accion asincrona
    Accion 2
    Accion 3
    Accion 4
    Fallada :fracaso 
*/
