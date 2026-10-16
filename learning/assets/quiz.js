// Shared recall-quiz checker for the teaching workspace.
// Each .quiz element needs data-answer (lowercase, trimmed match) on the
// outer .quiz div — the form itself lives one level inside that div.
function checkQuiz(form) {
  const quizBox = form.closest('.quiz');
  const input = form.querySelector('input[type="text"]');
  const feedback = form.querySelector('.feedback');
  const answer = quizBox.dataset.answer.trim().toLowerCase();
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
