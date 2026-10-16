// Shared recall-quiz checker for the teaching workspace.
// Each .quiz element needs data-answer (lowercase, trimmed match) on its form.
function checkQuiz(form) {
  const input = form.querySelector('input[type="text"]');
  const feedback = form.querySelector('.feedback');
  const answer = form.dataset.answer.trim().toLowerCase();
  const given = input.value.trim().toLowerCase();
  if (given === answer) {
    feedback.textContent = "Correct.";
    feedback.className = "feedback correct";
  } else {
    feedback.textContent = "Not quite — try again.";
    feedback.className = "feedback incorrect";
  }
  return false;
}
