for (let i = 0; i <= 5; i++) {
    const promesa = new Promise((resolve, reject) => {
        let random = Math.floor(Math.random() * 10000);
        console.log("Tarea " + i + " iniciada. Esperando " + random);
        setTimeout(() => {
            if (Math.random() > 0.4) {
                resolve("exito");
            } else {
                reject("fracaso");
            }
        }, random); // random es un delay entre 0 y 10 segundos
    })
        .then((value) => {
            console.log(value + " tarea " + i);
        })
        .catch((value) => {
            console.log(value + " tarea " + i);
        });
}

/* Ejmplo de salida posible:

Tarea 0 iniciada. Esperando 2135
Tarea 1 iniciada. Esperando 206
Tarea 2 iniciada. Esperando 9361
Tarea 3 iniciada. Esperando 3949
Tarea 4 iniciada. Esperando 7207
Tarea 5 iniciada. Esperando 5328
exito tarea 1
fracaso tarea 0
exito tarea 3
exito tarea 5
fracaso tarea 4
exito tarea 2

Tarea 0 iniciada. Esperando 8524
Tarea 1 iniciada. Esperando 9450
Tarea 2 iniciada. Esperando 9715
Tarea 3 iniciada. Esperando 9969
Tarea 4 iniciada. Esperando 4880
Tarea 5 iniciada. Esperando 9432
exito tarea 4
exito tarea 0
exito tarea 5
exito tarea 1
exito tarea 2
fracaso tarea 3
*/