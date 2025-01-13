# Contributing to Appledore

Welcome to Appledore, a graph library designed to simplify graph representation and manipulation! Thank you for considering contributing to this project. Whether you're fixing a bug, adding a feature, or improving documentation, your efforts are greatly appreciated.

---


## How to Contribute
1. **Create a issue**: If you have a suggestion for an enhancement, a feature you'd like to see added, or a fix for some problem related to existing code, then please open an issue in our repository's issues section. [issues](https://github.com/SharonIV0x86/Appledore/issues/new) .
2. **Issue assignment**: Wait till the issue is assigned to you, then you can work on the issue.
3. **Fork the repository** on GitHub.
4. **Clone your fork**:  
   ```bash
   git clone https://github.com/your-username/appledore.git
5. **Create a branch** for your feature or bug fix
    ```bash
    git checkout -b feature/your-feature-name
6. Write code and tests.
7. Submit a **pull request** (PR) with a clear description of your changes

# Contribution Guidelines.
## General Principles:
1. **Dedication to Assigned Issues**: 
    - If you are assigned to an issue, work on it with utmost dedication and aim to resolve it within a reasonable timeframe. Communicate proactively if you encounter challenges or delays.
2. **Timely Progress**
    - Maintain regular activity on your assigned tasks. If no updates are provided on an issue or pull request (PR) for more than 3 days, it will be marked as stale.

## Issue Management:
3. **Issue Assignment**: 
    - If you are already assigned to one of the issues, you must get its corresponding pull request at least **approved** regardless if its merged or not. If your PR is at least approved only then you can start working on a new issue and get it assigned to you.
4. **Inactive Issues**:
    - Issues that remain inactive for **3 days** after assignment will be marked as stale and **12 hours** after being marked as stale the issue will be reassigned to another contributor to ensure timely resolution.
5. **Request for Extensions**:
    - If you need more time to work on an issue, notify the maintainer before the issue is marked stale to avoid reassignment.
## Pull Request (PR) Management:
6. **Latest Changes**: 
    - If you opened a PR, make sure it is in **sync** with the latest changes from **main** branch of the repository. Make sure to timely run ``git pull`` on your forks and branches to pull latest changes from the main repository. Otherwise it will be difficult for maintainer(s) to **test** your fix or feature if your code is multiple commits behind the main branch. 
7. **Inactive Pull Requests**:
    - PRs that remain inactive for **3 days** will be marked as stale, and after **12 hours**, they will be closed if no further activity occurs. The corresponding issue will also be unassigned from the contributor.
8. **Quality of PRs**:
    - Ensure that your PRs ahdere to project's coding standards and include necessary, documentation, test cases, and meaningful commit messages.
## Additional Notes:
9. **Open Discussions**:
    - Before starting work on significant issues or features, discuss your approach with the maintainers to ensure alignment and avoid duplication of efforts.
10. **Communication is Key**:
    - Use the project’s communication channels (e.g. Discord, or GitHub Discussions) to ask questions, seek clarification, or discuss ideas related to your assigned tasks.
11. **Peer Reviews**:
    - Actively participate in reviewing other contributors’ PRs when possible. Constructive feedback strengthens the project and fosters collaboration.

## Documentation and Examples
- Improve the API documentation to make it beginner-friendly.
- Write tutorials and example programs showcasing common use cases of the library.
- You can contribute towards documentation either by mentioning doxygen docstrings above functions and classes, or contribute markdown files for the wiki.

## Coding Guidelines
- Follow modern C++ best practices such as RAII (Resource Acquisition Is Initialization), avoiding raw pointers where possible, and using STL containers effectively.
- Use meaningful names for variables, functions, and classes.
- Maintain consistent indentation and formatting (4 spaces per indentation level is recommended).
- Document all public-facing methods using comments or docstrings.
- Ensure code compiles without warnings and passes all tests before submission.
