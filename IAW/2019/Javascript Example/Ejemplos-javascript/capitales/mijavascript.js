
var capitales=new Array();
capitales["Francia"]="Paris";
capitales["Alemania"]="Berlín";
capitales["Chile"]="Santiago";
capitales["Australia"]="Canberra";
capitales["México"]="Mexico DF";

function descubrir(elemento){
	pais=elemento.innerHTML;
	capital=elemento.nextSibling;
	capital.innerHTML = capitales[pais]; 
}

function cubrir(elemento){
	elemento.nextSibling.innerHTML = ""; 
}