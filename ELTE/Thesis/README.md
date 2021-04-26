## Eötvös Loránd University, Budapest (2017-2020)

### Thesis

- Title: Diagnosing vulnerabilities with static analysis
    - [Thesis](./Thesis.pdf)
    - Checkers for LLVM Clang-Tidy:
        - [Spuriously wake up function](https://github.com/llvm/llvm-project/commit/0f4c70dd3ec6d7ee831f868e3e483273daec18f0)
        - [Bad signal to kill thread](https://github.com/llvm/llvm-project/commit/8d288a0668a574863d52784084ff565c89f7366e)
        - [Signal in multithreaded program](https://reviews.llvm.org/D75229) (under review)
        - [Do not refer atomic twice](https://reviews.llvm.org/D77493) (under review)
    - Implemented test environment: [Clang Test Docker](https://github.com/abelkocsis/clang-test-docker)