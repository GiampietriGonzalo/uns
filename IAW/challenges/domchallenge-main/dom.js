/* CHALLENGE 1
1. Find the second paragraph on the page
2. Add a class of "highlight", or
3. Remove the class of "highlight" if already present
e.g. "<p class="para">Hello</p>" -> "<p class="para highlight">Hello</p>"
*/
function toggleHighlight() {
  //should be highlighted gold when you click the button. If you click it again the gold highlight should go away.
  const highlightedParagraphs = document.getElementsByClassName("highlight");

  if (highlightedParagraphs.length > 0) {
    highlightedParagraphs[0].className = "font-serif";
  } else {
    document.getElementsByClassName("font-serif")[1].className = "highlight";
  }
}

/* CHALLENGE 2
1. Take an array of strings as a parameter
1. Return a new `ul` containing an `li` containing a string for each element in the array
e.g. generateList(["hello", "world"]) -> <ul>
                                           <li>hello</li>
                                           <li>world</li>
                                          </ul>
*/
function generateList(array) {
  if (document.getElementsByTagName("ul").length > 0) {
    return;
  } 

  const ul = document.createElement("ul");

  array.forEach(item => {
    const li = document.createElement("li");
    li.textContent = item;
    ul.appendChild(li);
  });

  return ul;
}

/* CHALLENGE 3a
1. Take a `textarea` element as a parameter
2. Count how many characters have been typed into it
3. If it contains > 140 characters set the `aria-invalid="true"` attribute
*/
function validateTweet(textarea) {
  if (textarea.value.length > 140) {
    textarea.setAttribute('aria-invalid','true');
  } else {
    textarea.setAttribute('aria-invalid','false');
  }
}

/* CHALLENGE 3b
1. Find the textarea with ID "tweet"
2. Whenever a user types into it validate it using the previous function
*/
function validateTweetOnInput() {
  const element = document.getElementById("tweet");
  element.addEventListener('input', function() {
    validateTweet(element);
  });
}

/* CHALLENGE 4
1. Find all buttons with a classname of "toggle-button"
2. When each button is clicked show/hide the next sibling following the button
e.g. <button class="toggle-button">Toggle</button>
     <p>This should appear/disappear when the button is clicked</p>
*/
function setupToggleButtons() {
  const buttons = document.getElementsByClassName("toggle-button");
  const array = [...buttons];

  array.forEach(button => {
    const sibling = button.nextElementSibling;

    button.addEventListener('click', function() {
      if (sibling.style.display == 'none') {
        sibling.style.display = '';
      } else {
        sibling.style.display = 'none';
      }
    }); 
  });
}
