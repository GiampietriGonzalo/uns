const chat = document.getElementById('chat');
const button = document.getElementById('add-btn');

const userUrl = 'https://randomuser.me/api/';
const commentUrl = 'https://randommer.io/api/Text/Review?product=movie&quantity=1';

const RANDOMMER_API_KEY = "b0615ed73a5c42b6a830d55c0011ec5f";

async function getUser() {
  const res = await fetch(userUrl);
  const data = await res.json();
  const user = data.results[0];

  return {
    name: `${user.name.first} ${user.name.last}`,
    age: user.dob.age,
    id: user.login.uuid,
    avatar: user.picture.medium
  };
}

function getComment() {
  return fetch(commentUrl, {
    method: "POST",
    headers: {
      'X-Api-Key': RANDOMMER_API_KEY
    }
  })
  .then(res => res.json())
  .then(data => data[0]);
}

function renderMessage(user, text) {
  const msg = document.createElement('div');
  msg.className = 'message';

  msg.innerHTML = `
    <img src="${user.avatar}" alt="${user.name}" />
    <div class="text-content">
      <div class="username">${user.name}</div>
      <div class="text">${text}</div>
    </div>
  `;

  chat.appendChild(msg);
  chat.scrollTop = chat.scrollHeight;
}

button.addEventListener('click', async () => {
  const user = await getUser();
  const comment = await getComment();
  renderMessage(user, comment);
});

