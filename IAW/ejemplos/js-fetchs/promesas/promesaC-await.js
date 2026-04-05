function prometerNSec(x) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(x);
    }, 5000);
  });
}

async function Promesa1() {
  let x = await prometerNSec(10);
  console.log("Promesa 1 terminada -> " + x);
}

 function Promesa2() {
  let x = prometerNSec(20);
  console.log("Promesa 2 lanzada! Pero aun no se como termina ->" + x);
}


console.log("Invocamos Promesa1")
Promesa1();
console.log("Invocamos Promesa2")
Promesa2();
console.log("Todo invocado!")


/*
Resultado:
  Invocamos Promesa1
  Invocamos Promesa2
  Promesa 2 lanzada! Pero aun no se como termina ->[object Promise]
  Todo invocado!
  Promesa 1 terminada -> 10

Explicación:
- Promesa1 se ejecuta y se detiene en el await (pPor ser async) hasta que prometerNSec se resuelva, lo que tarda 5 segundos.
- Mientras tanto, Promesa2 (no async) se ejecuta y lanza la promesa pero no espera a que se resuelva, por lo que imprime el mensaje con el objeto Promise sin resolver.
- Finalmente, después de 5 segundos, Promesa1 se resuelve y se imprime el resultado.
*/