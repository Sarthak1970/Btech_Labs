import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin
import time

class SimpleWebCrawler:
    def __init__(self, start_url, max_depth=2, sleep_time=1):
        self.start_url = start_url
        self.max_depth = max_depth
        self.visited = set()
        self.sleep_time = sleep_time

    def fetch(self, url):
        """Fetch the content of a URL."""
        try:
            response = requests.get(url)
            response.raise_for_status()
            return response.text
        except requests.exceptions.RequestException as e:
            print(f"Failed to fetch {url}: {e}")
            return None

    def parse_links(self, html, base_url):
        """Parse all unique links from the HTML."""
        soup = BeautifulSoup(html, 'html.parser')
        links = set()
        for anchor in soup.find_all('a', href=True):
            link = urljoin(base_url, anchor['href'])
            if link.startswith('http'):  # Only include absolute URLs
                links.add(link)
        return links

    def crawl(self, url, depth=0):
        """Crawl the web starting from a given URL up to a certain depth."""
        if depth > self.max_depth or url in self.visited:
            return

        print(f"Crawling: {url} (Depth: {depth})")
        self.visited.add(url)

        html_content = self.fetch(url)
        if not html_content:
            return

        links = self.parse_links(html_content, url)
        for link in links:
            self.crawl(link, depth + 1)
            time.sleep(self.sleep_time)

def scrape_page(url):
    """Scrape a webpage to extract relevant data (e.g., titles and headings)."""
    print(f"\nScraping {url}...")
    html_content = requests.get(url).text
    soup = BeautifulSoup(html_content, 'html.parser')

    # Extract page title
    title = soup.title.string if soup.title else "No title"
    print(f"Page Title: {title}")

    # Extract all H1 headings
    h1_headings = [h1.get_text(strip=True) for h1 in soup.find_all('h1')]
    print(f"H1 Headings: {h1_headings}")

    # Extract all paragraph text
    paragraphs = [p.get_text(strip=True) for p in soup.find_all('p')]
    print(f"Paragraphs: {paragraphs[:5]}")  # Display first 5 paragraphs

if __name__ == "__main__":
    start_url = "https://yahoo.com"

    # Build a simple crawler to explore a website
    crawler = SimpleWebCrawler(start_url, max_depth=1)
    crawler.crawl(start_url)

    # Scrape a specific page
    scrape_page(start_url)
