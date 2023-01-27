
<link  href="style.css" rel="stylesheet"></link>

<h1> TP : Canon Projet </h1>

<h2> Groupe : </h2>  

<div class= name>
    <ul>
        <li>Emma Massauteau
        <li>Bruno Gomes
        <li>Bryan Bachelet
    </ul>
</div>

<hr>
<h2> 1. Introduction : </h2>
<div class = intro>
    <div class = description>
Pour ce projet de physique, l'objectif était d'implémenter un canon qui propulse un balle. Nous devions appliqué sur ce projectile les équations de mouvement cinématiques dans un premier temps. La suite était d'implémenter un frottement du canon sur la balle puis celui de l'air et enfin d'applique la collision entre le canon et la balle lors du tir.
 </div>
    <div class = imageProject>
<img src = "Images/Project1.png">
    </div>
</div>

<div class = Chapter>
    <h2> 2. Trajectoire Cinematique :</h2>
    <div class = cinematique>
        <div class = description>
            Pour l'implémentation de la trajectoire cinématique à notre balle, nous d'abord mis en place les équations de mouvement classique puis nous avons appliquer la méthode de l'Euler fait pour l'implémentation numérique afin de résoudre par approximation des équations différentielles du premier ordre avec un condition initiale. Voici la méthode d'Euler : <a href = "https://fr.wikipedia.org/wiki/M%C3%A9thode_d%27Euler"> ici </a>
        </div>
        <div class = imageProject>
            <div class = img1> 
                <img src = "Images/Formule3.png" alt ="Formule">
            </div>
            <img src = "Images/Formule4.png" alt ="Formule">
        </div>
    </div>
</div>


<div class = Chapter>
    <h2> 3. Frottement du Canon</h2>
    <div class = intro>
        <div class = description>
        Pour le frottement de canon, nous avons appliqué un frottement de solide contre solide en utilisant le coffecient de Acier / Acier qui de 0.2 afin de modifier la vitesse initiale de notre projectile.
        </div>
        <div class = imageProject>
            <img src = "Images/Formule5.png" alt ="Formule">
            <img src = "Images/Formule6.png" alt ="Formule">
        </div>
    </div>
</div>

<h2> Frottement l'air : </h2>
Pour le frottement de l'air,

<h2> Collision du canon </h2>  
Pour la collision du canon avec la balle, on applique une collision inélastique sur le canon et un frottement solide contre solide pour le ralentir après le tir. 
<img src = "Img.png" alt ="Formule">
<h2> Features Additionnels : </h2>
Prediciton de tir
Type d'environement
<h2> Crédits : </h2>
Pour réaliser ce projet, nous avons utilisé plusieurs librairies : 
<ul>
    <li> Raylib 
    <li> Dear ImGUI
</ul>




