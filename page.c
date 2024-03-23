#include "os.h"

// defined in mem.S
extern uint32_t TEXT_START;
extern uint32_t TEXT_END;
extern uint32_t DATA_START;
extern uint32_t DATA_END;
extern uint32_t RODATA_START;
extern uint32_t RODATA_END;
extern uint32_t BSS_START;
extern uint32_t BSS_END;
extern uint32_t HEAP_START;
extern uint32_t HEAP_SIZE;

static uint32_t _alloc_start = 0;
static uint32_t _alloc_end = 0;
static uint32_t _num_pages = 0;

#define PAGE_SIZE 4096
#define PAGE_ORDER 12

#define PAGE_TAKEN (uint8_t)(1 << 0)
#define PAGE_LAST (uint8_t)(1 << 1)

struct Page
{
  uint8_t flags;
};

static inline void _clear(struct Page *page)
{
  page->flags = 0;
}

static inline int _is_free(struct Page *page)
{
  if (page->flags & PAGE_TAKEN)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

static inline int _is_last(struct Page *page)
{
  if (page->flags & PAGE_LAST)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

static inline void _set_flag(struct Page *page, uint8_t flags)
{
  page->flags |= flags;
}

// align the address to the border of page(4K)
static inline uint32_t _align_page(uint32_t address)
{
  uint32_t order = (1 << PAGE_ORDER) - 1;
  // 0x0000_0000_0000_0000_0001_0000_0000_0000 - 1 = 4096 - 1
  // 0x0000_0000_0000_0000_0000_FFFF_FFFF_FFFF
  return (address + order) & (~order);
}

void page_init()
{
  // reserved 8 Page (8 x 4096) to hold the Page structures.
  // to manage at most 128 MB (8 x 4096 x 4096)
  _num_pages = (HEAP_SIZE / PAGE_SIZE) - 8;
  printf("HEAP_START = %x, HEAP_SIZE = %x, num of pages = %d\n", HEAP_START, HEAP_SIZE, _num_pages);
  struct Page *page = (struct Page *)HEAP_START;
  for (int i = 0; i < _num_pages; i++)
  {
    _clear(page);
    page++;
  }
  // ignore 8 to manage all
  _alloc_start = _align_page(HEAP_START + 8 * PAGE_SIZE);
  // the end of heap
  _alloc_end = _alloc_start + (PAGE_SIZE * _num_pages);

  printf("TEXT:   0x%x -> 0x%x\n", TEXT_START, TEXT_END);
  printf("RODATA: 0x%x -> 0x%x\n", RODATA_START, RODATA_END);
  printf("DATA:   0x%x -> 0x%x\n", DATA_START, DATA_END);
  printf("BSS:    0x%x -> 0x%x\n", BSS_START, BSS_END);
  printf("HEAP:   0x%x -> 0x%x\n", _alloc_start, _alloc_end);
}

void *page_alloc(int npages)
{
  int found = 0;
  struct Page *page_i = (struct Page *)HEAP_START;
  for (int i = 0; i <= (_num_pages - npages); i++)
  {
    if (_is_free(page_i))
    {
      found = 1;
      struct Page *page_j = page_i + 1;
      for (int j = i + 1; j < (i + npages); j++)
      {
        if (!_is_free(page_j))
        {
          found = 0;
          break;
        }
        page_j++;
      }

      if (found)
      {
        struct Page *page_k = page_i;
        for (int k = i; k < (i + npages); k++)
        {
          _set_flag(page_k, PAGE_TAKEN);
          page_k++;
        }
        page_k--;
        _set_flag(page_k, PAGE_LAST);
        return (void *)(_alloc_start + i * PAGE_SIZE);
      }
    }
    page_i++;
  }
  return NULL;
}

void page_free(void *p)
{
  if (!p || (uint32_t)p >= _alloc_end)
  {
    return;
  }

  struct Page *page = (struct Page *)HEAP_START;
  page += ((uint32_t)p - _alloc_start) / PAGE_SIZE;
  while (!_is_free(page))
  {
    if (_is_last(page))
    {
      _clear(page);
      break;
    }
    else
    {
      _clear(page);
      page++;
    }
  }
}

void page_test()
{
  void *p = page_alloc(2);
  printf("p = 0x%x\n", p);

  void *p2 = page_alloc(7);
  printf("p2 = 0x%x\n", p2);
  page_free(p2);

  void *p3 = page_alloc(4);
  printf("p3 = 0x%x\n", p3);
}