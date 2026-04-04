<?php
	// ============================================================
	// PROCESAMIENTO - Aquí se realiza toda la lógica PHP
	// ============================================================

	// Obtengo los nombres del request. Aqui se usa el arreglo global _REQUEST
	$nombre = $_REQUEST["nombreusuario"];
	$personaje = $_REQUEST["personaje"];

	// Un arreglo asociativo que vincula los personajes con los actores reales.
	$voces = array(
		"Homero" => "Dan Castellaneta",
		"Duffman" => "Hank Azaria",
		"Frank Grimes" => "Hank Azaria",
		"Troy McLure" => "Phil Hartman"
	);

	// Procesar los datos
	$mensaje = "¡Hola $nombre! Has elegido a <strong>$personaje</strong>, cuya voz es la de <strong>$voces[$personaje]</strong>";
	$rutaImagenPersonaje = "imagenes/" . strtolower($personaje) . ".jpg";
	$rutaImagenActor = "imagenes/" . strtolower($voces[$personaje]) . ".jpg";
	$rutaFlecha = "imagenes/flecha.png";

?>
<!DOCTYPE html>
<html lang="es">

<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Voces - Los Simpsons</title>
	<link rel="stylesheet" href="estilos.css">
</head>

<body class="pagina-resultados">
	<div class="contenedor">
		<!-- ============================================================ -->
		<!-- SALIDA - Aquí se vuelca el resultado procesado -->
		<!-- ============================================================ -->
		<div class="mensaje"><?php echo $mensaje; ?></div>

		<!-- Imágenes con los datos ya procesados -->
		<div class="galeria">
			<img src="<?php echo $rutaImagenPersonaje; ?>" alt="<?php echo $personaje; ?>">
			<img src="<?php echo $rutaFlecha; ?>" alt="flecha" style="max-width: 40px;">
			<img src="<?php echo $rutaImagenActor; ?>" alt="<?php echo $voces[$personaje]; ?>">
		</div>
		
		<div class="volver">
			<a href="index.html">← Volver y elegir otro personaje</a>
		</div>
	</div>
</body>

</html>