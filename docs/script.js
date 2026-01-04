document.addEventListener('DOMContentLoaded', () => {
    const mobileHeader = document.querySelector('.mobile-header');
    const menuToggle = document.getElementById('menu-toggle');
    const sidebar = document.getElementById('sidebar');
    const navItems = document.querySelectorAll('.nav-item');
    const sections = document.querySelectorAll('section');

    // Mobile Menu Toggle
    menuToggle.addEventListener('click', () => {
        sidebar.classList.toggle('open');
        const isOpen = sidebar.classList.contains('open');
        menuToggle.innerHTML = isOpen 
            ? '<svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><line x1="18" y1="6" x2="6" y2="18"></line><line x1="6" y1="6" x2="18" y2="18"></line></svg>'
            : '<svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><line x1="3" y1="12" x2="21" y2="12"></line><line x1="3" y1="6" x2="21" y2="6"></line><line x1="3" y1="18" x2="21" y2="18"></line></svg>';
    });

    // Close mobile menu when a link is clicked
    navItems.forEach(item => {
        item.addEventListener('click', () => {
            if (window.innerWidth <= 768) {
                sidebar.classList.remove('open');
            }
        });
    });

    // Active Link Highlighting on Scroll
    const observerOptions = {
        root: null,
        rootMargin: '-20% 0px -60% 0px', // Trigger when section is near top
        threshold: 0
    };

    const observer = new IntersectionObserver((entries) => {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                // Remove active from all
                navItems.forEach(nav => nav.classList.remove('active'));
                
                // Add active to current
                const id = entry.target.getAttribute('id');
                const activeLink = document.querySelector(`.nav-item[href="#${id}"]`);
                if (activeLink) {
                    activeLink.classList.add('active');
                }
            }
        });
    }, observerOptions);

    sections.forEach(section => {
        observer.observe(section);
    });

    // Search input highlight effect (visual only for now)
    const searchInput = document.getElementById('search-input');
    searchInput.addEventListener('focus', () => {
        document.querySelector('.search-container').style.opacity = '1';
    });
});
