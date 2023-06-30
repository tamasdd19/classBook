<h1>ClassBook</h1>

<p>ClassBook is a C++ project that provides a graphical user interface (GUI) for managing student and professor data. It utilizes SFML for GUI implementation and SQLite3 for efficient database management. The project offers a login page with username and password authentication, followed by separate functionalities for students and professors.</p>

<h2>Features</h2>

<h3>Login</h3>

![loginPage](https://github.com/tamasdd19/classBook/assets/118727728/70ff779e-93ba-4ea9-b35d-1b1eab12d162)
<ul>
  <li>Users are required to provide their username and password to access the system.</li>
  <li>The login page verifies the credentials and grants access to the respective user roles.</li>
</ul>

<h3>Student Side</h3>

![studentMain](https://github.com/tamasdd19/classBook/assets/118727728/adfaf906-1217-4cc0-ad7e-8e809e0e3b92)

<ul>
  <li>Student users have access to three main options:</li>
  <ul>
    <li><strong>Student's Data</strong>: Provides basic information about the student.</li>
    <li><strong>Grades</strong>: Displays the grades for the courses the student is attending.</li>
    <li><strong>Exit</strong>: Allows the student to exit the application.</li>
  </ul>
</ul>

<h3>Professor Side</h3>

![ProfessorMain](https://github.com/tamasdd19/classBook/assets/118727728/bdf7a29f-3735-4286-99e1-6149dca0f29c)
<ul>
  <li>Professor users have access to three main options:</li>
  <ul>
    <li><strong>Professor's Data</strong>: Displays basic information about the professor.</li>
    <li><strong>Gradebook</strong>: Enables the professor to assign grades.</li>
    <ul>
      <li>The gradebook lists all the courses the professor is teaching.</li>
      <li>Upon selecting a course, the professor can view a list of students attending that course.</li>
      <li>The professor can then assign grades to individual students.</li>
    </ul>
    <li><strong>Exit</strong>: Allows the professor to exit the application.</li>
  </ul>
</ul>

<h2>Dependency</h2>

<p>The ClassBook project has the following dependency:</p>
<ul>
  <li>MinGW: version 13.1.0 is needed to compile the sfml code. This is only if you want to recompile the project</li>
</ul>

<p>Make sure to install the dependency before compiling the project.</p>

<h2>Installation</h2>

<p>To run the ClassBook project on your local machine, follow these steps:</p>

<ol>
  <li>Clone the repository to your local machine using the following command:</li>
</ol>

<pre><code>git clone https://github.com/tamasdd19/classBook.git</code></pre>

<ol start="2">
  <li>Navigate to the project directory:</li>
</ol>

<pre><code>cd classBook</code></pre>

<ol start="3">
  <li>To compile and run the project you need to use:</li>
</ol>
  <pre><code>make run</code></pre>
<ol start="3">
  <li>If you just want to run the project you can just click the classBook.exe file in the main folder or use:</li>
</ol>

<pre><code>./classBook</code></pre>

<h2>Usage</h2>

<p>Upon launching the ClassBook application, you will be presented with a login page. Enter your username and password to access the system. Depending on your user role (student or professor), you will have access to different features and functionalities.</p>


<p>Navigate through the menus by clicking on the desired options. Follow the on-screen instructions to interact with the system and perform various tasks such as viewing student data, grades, professor data, and assigning grades.</p>

<p>For testing purposes I have created 4 users, 2 students and 2 professors. The usernames are: Student1, Student2, Prof1, Prof2 and they all have the same password, test. Feel free to try out my project!


<h2>Acknowledgments</h2>

<ul>
  <li><a href="https://www.sfml-dev.org/">SFML</a>: The Simple and Fast Multimedia Library.</li>
  <li><a href="https://www.sqlite.org/">SQLite</a>: A C library for efficient database management.</li>
</ul>
