// imporst
const express = require('express');
const path = require('path');
const { movies } = require('./peliculas');

// start
const app = express();
const PORT = process.env.PORT || 3000;

// middleware
app.use(express.static(path.join(__dirname, 'public')));

// routes
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

// todas las peliculas
app.get('/pelis', (req, res) => {
    res.json(movies);
});

// peliculas por año
app.get('/pelis/year/:year', (req, res) => {
    const year = parseInt(req.params.year);
    const filtered = movies.filter(m => m.year === year);

    if (filtered.length === 0) {
        return res.status(404).json({ error: 'No se encontraron películas para ese año' });
    }

    res.json(filtered);
});

// peliculas con titulo 'title'
app.get('/pelis/title/:title', (req, res) => {
    const title = req.params.title.toLowerCase();
    const filtered = movies.filter(m => m.title.toLowerCase().includes(title));

    if (filtered.length === 0) {
        return res.status(404).json({ error: 'No se encontraron películas con ese título' });
    }

    res.json(filtered);
});

// promedio de scores por director
app.get('/pelis/promedio/:director', (req, res) => {
    const director = req.params.director;
    const filtered = movies.filter(m => m.director.toLowerCase() === director.toLowerCase());

    if (filtered.length === 0) {
        return res.status(404).json({ error: 'No se encontraron películas para ese director' });
    }

    const promedio = filtered.reduce((acc, m) => acc + m.score, 0) / filtered.length;

    res.json({ director, promedio });
});

// start server
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});