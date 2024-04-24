from collections.abc import Iterator
from typing import Annotated

from lib.array import Array
from lib.errors import EmptyCollectionError
from lib.test import Test
from lib.test.annotations import *
from lib.type_vars import Item, Priority

from lab4.core.merge_sort import merge_sort
from lab9.core.avl_tree_priority_queue.exercise import AVLTreePriorityQueue


@Test
def max_enqueue_on_empty_then_get_length(
    priority: Priority,
    item: Item,
):
    priority_queue = AVLTreePriorityQueue()
    priority_queue.enqueue(priority, item)
    yield 1
    yield priority_queue.get_length()


@Test
def min_enqueue_on_empty_then_get_length(
    priority: Priority,
    item: Item,
):
    priority_queue = AVLTreePriorityQueue(is_max=False)
    priority_queue.enqueue(priority, item)
    yield 1
    yield priority_queue.get_length()


def contains_priority(priority: Priority, items: Iterator[tuple[Priority, Item]]) -> bool:
    return bool([() for p, _ in items if p == priority])


@Test
def max_enqueue_on_non_empty_then_get_length(
    items: Annotated[Array[tuple[Priority, Item]], GE(1)],
    priority: Priority,
    item: Item,
):
    priority_queue = AVLTreePriorityQueue.build(items.iterator())
    if contains_priority(priority, items.iterator()):
        length = priority_queue.get_length()
    else:
        length = priority_queue.get_length() + 1
    priority_queue.enqueue(priority, item)
    yield length
    yield priority_queue.get_length()


@Test
def min_enqueue_on_non_empty_then_get_length(
    items: Annotated[Array[tuple[Priority, Item]], GE(1)],
    priority: Priority,
    item: Item,
):
    priority_queue = AVLTreePriorityQueue.build(items.iterator(), is_max=False)
    if contains_priority(priority, items.iterator()):
        length = priority_queue.get_length()
    else:
        length = priority_queue.get_length() + 1
    priority_queue.enqueue(priority, item)
    yield length
    yield priority_queue.get_length()


@Test
def max_enqueue_all_on_empty_then_front(
    items: Annotated[Array[tuple[Priority, Item]], GE(1)],
):
    priority_queue = AVLTreePriorityQueue()
    front_priority, front_item = items.get_at(0)
    for priority, item in items.iterator():
        if priority >= front_priority:
            front_priority, front_item = priority, item
        priority_queue.enqueue(priority, item)
    yield front_priority, front_item
    yield priority_queue.front()


@Test
def min_enqueue_all_on_empty_then_front(
    items: Annotated[Array[tuple[Priority, Item]], GE(1)],
):
    priority_queue = AVLTreePriorityQueue(is_max=False)
    front_priority, front_item = items.get_at(0)
    for priority, item in items.iterator():
        if priority <= front_priority:
            front_priority, front_item = priority, item
        priority_queue.enqueue(priority, item)
    yield front_priority, front_item
    yield priority_queue.front()


@Test
def max_enqueue_all_on_non_empty_then_front(
    initial_items: Annotated[Array[tuple[Priority, Item]], GE(1)],
    items: Annotated[Array[tuple[Priority, Item]], GE(1)],
):
    priority_queue = AVLTreePriorityQueue.build(initial_items.iterator())
    front_priority, front_item = priority_queue.front()
    for priority, item in items.iterator():
        if priority >= front_priority:
            front_priority, front_item = priority, item
        priority_queue.enqueue(priority, item)
    yield front_priority, front_item
    yield priority_queue.front()


@Test
def min_enqueue_all_on_non_empty_then_front(
    initial_items: Annotated[Array[tuple[Priority, Item]], GE(1)],
    items: Annotated[Array[tuple[Priority, Item]], GE(1)],
):
    priority_queue = AVLTreePriorityQueue.build(initial_items.iterator(), is_max=False)
    front_priority, front_item = priority_queue.front()
    for priority, item in items.iterator():
        if priority <= front_priority:
            front_priority, front_item = priority, item
        priority_queue.enqueue(priority, item)
    yield front_priority, front_item
    yield priority_queue.front()


@Test
def max_enqueue_all_on_empty_then_dequeue(
    items: Annotated[Array[tuple[Priority, Item]], GE(1)],
):
    priority_queue = AVLTreePriorityQueue()
    front_priority, front_item = items.get_at(0)
    for priority, item in items.iterator():
        if priority >= front_priority:
            front_priority, front_item = priority, item
        priority_queue.enqueue(priority, item)
    yield front_priority, front_item
    yield priority_queue.dequeue()


@Test
def min_enqueue_all_on_empty_then_dequeue(
    items: Annotated[Array[tuple[Priority, Item]], GE(1)],
):
    priority_queue = AVLTreePriorityQueue(is_max=False)
    front_priority, front_item = items.get_at(0)
    for priority, item in items.iterator():
        if priority <= front_priority:
            front_priority, front_item = priority, item
        priority_queue.enqueue(priority, item)
    yield front_priority, front_item
    yield priority_queue.dequeue()


@Test
def max_enqueue_all_on_non_empty_then_dequeue(
    initial_items: Annotated[Array[tuple[Priority, Item]], GE(1)],
    items: Annotated[Array[tuple[Priority, Item]], GE(1)],
):
    priority_queue = AVLTreePriorityQueue.build(initial_items.iterator())
    front_priority, front_item = priority_queue.front()
    for priority, item in items.iterator():
        if priority >= front_priority:
            front_priority, front_item = priority, item
        priority_queue.enqueue(priority, item)
    yield front_priority, front_item
    yield priority_queue.dequeue()


@Test
def min_enqueue_all_on_non_empty_then_dequeue(
    initial_items: Annotated[Array[tuple[Priority, Item]], GE(1)],
    items: Annotated[Array[tuple[Priority, Item]], GE(1)],
):
    priority_queue = AVLTreePriorityQueue.build(initial_items.iterator(), is_max=False)
    front_priority, front_item = priority_queue.front()
    for priority, item in items.iterator():
        if priority <= front_priority:
            front_priority, front_item = priority, item
        priority_queue.enqueue(priority, item)
    yield front_priority, front_item
    yield priority_queue.dequeue()


@Test
def max_enqueue_all_on_empty_then_get_length(
    items: Annotated[Array[tuple[Priority, Item]], GE(1)],
):
    priority_queue = AVLTreePriorityQueue()
    length = 0
    for priority, item in items.iterator():
        if not contains_priority(priority, priority_queue.iterator()):
            length += 1
        priority_queue.enqueue(priority, item)
    yield length
    yield priority_queue.get_length()


@Test
def min_enqueue_all_on_empty_then_get_length(
    items: Annotated[Array[tuple[Priority, Item]], GE(1)],
):
    priority_queue = AVLTreePriorityQueue(is_max=False)
    length = 0
    for priority, item in items.iterator():
        if not contains_priority(priority, priority_queue.iterator()):
            length += 1
        priority_queue.enqueue(priority, item)
    yield length
    yield priority_queue.get_length()


@Test
def max_enqueue_all_on_non_empty_then_get_length(
    initial_items: Annotated[Array[tuple[Priority, Item]], GE(1)],
    items: Annotated[Array[tuple[Priority, Item]], GE(1)],
):
    priority_queue = AVLTreePriorityQueue.build(initial_items.iterator())
    length = priority_queue.get_length()
    for priority, item in items.iterator():
        if not contains_priority(priority, priority_queue.iterator()):
            length += 1
        priority_queue.enqueue(priority, item)
    yield length
    yield priority_queue.get_length()


@Test
def min_enqueue_all_on_non_empty_then_get_length(
    initial_items: Annotated[Array[tuple[Priority, Item]], GE(1)],
    items: Annotated[Array[tuple[Priority, Item]], GE(1)],
):
    priority_queue = AVLTreePriorityQueue.build(initial_items.iterator(), is_max=False)
    length = priority_queue.get_length()
    for priority, item in items.iterator():
        if not contains_priority(priority, priority_queue.iterator()):
            length += 1
        priority_queue.enqueue(priority, item)
    yield length
    yield priority_queue.get_length()


@Test
def max_front_on_empty():
    priority_queue = AVLTreePriorityQueue()
    yield EmptyCollectionError
    yield priority_queue.front()


@Test
def min_front_on_empty():
    priority_queue = AVLTreePriorityQueue(is_max=False)
    yield EmptyCollectionError
    yield priority_queue.front()


@Test
def max_front_on_non_empty(items: Annotated[Array[tuple[Priority, Item]], GE(1)]):
    sorted_items = Array.build(items.iterator())
    merge_sort(sorted_items)
    priority_queue = AVLTreePriorityQueue.build(items.iterator())
    expect_priority, _ = sorted_items.get_at(sorted_items.get_length() - 1)
    actual_priority, _ = priority_queue.front()
    yield expect_priority
    yield actual_priority


@Test
def min_front_on_non_empty(items: Annotated[Array[tuple[Priority, Item]], GE(1)]):
    sorted_items = Array.build(items.iterator())
    merge_sort(sorted_items)
    priority_queue = AVLTreePriorityQueue.build(items.iterator(), is_max=False)
    expect_priority, _ = sorted_items.get_at(0)
    actual_priority, _ = priority_queue.front()
    yield expect_priority
    yield actual_priority


@Test
def max_front_on_non_empty_then_get_length(items: Annotated[Array[tuple[Priority, Item]], GE(1)]):
    priority_queue = AVLTreePriorityQueue.build(items.iterator())
    length = priority_queue.get_length()
    priority_queue.front()
    yield length
    yield priority_queue.get_length()


@Test
def min_front_on_non_empty_then_get_length(items: Annotated[Array[tuple[Priority, Item]], GE(1)]):
    priority_queue = AVLTreePriorityQueue.build(items.iterator(), is_max=False)
    length = priority_queue.get_length()
    priority_queue.front()
    yield length
    yield priority_queue.get_length()


@Test
def max_dequeue_on_empty():
    priority_queue = AVLTreePriorityQueue()
    yield EmptyCollectionError
    yield priority_queue.dequeue()


@Test
def min_dequeue_on_empty():
    priority_queue = AVLTreePriorityQueue(is_max=False)
    yield EmptyCollectionError
    yield priority_queue.dequeue()


@Test
def max_dequeue_on_non_empty(items: Annotated[Array[tuple[Priority, Item]], GE(1)]):
    sorted_items = Array.build(items.iterator())
    merge_sort(sorted_items)
    priority_queue = AVLTreePriorityQueue.build(items.iterator())
    expect_priority, _ = sorted_items.get_at(sorted_items.get_length() - 1)
    actual_priority, _ = priority_queue.dequeue()
    yield expect_priority
    yield actual_priority


@Test
def min_dequeue_on_non_empty(items: Annotated[Array[tuple[Priority, Item]], GE(1)]):
    sorted_items = Array.build(items.iterator())
    merge_sort(sorted_items)
    priority_queue = AVLTreePriorityQueue.build(items.iterator(), is_max=False)
    expect_priority, _ = sorted_items.get_at(0)
    actual_priority, _ = priority_queue.dequeue()
    yield expect_priority
    yield actual_priority


@Test
def max_dequeue_on_non_empty_then_get_length(items: Annotated[Array[tuple[Priority, Item]], GE(1)]):
    priority_queue = AVLTreePriorityQueue.build(items.iterator())
    length = priority_queue.get_length() - 1
    priority_queue.dequeue()
    yield length
    yield priority_queue.get_length()


@Test
def min_dequeue_on_non_empty_then_get_length(items: Annotated[Array[tuple[Priority, Item]], GE(1)]):
    priority_queue = AVLTreePriorityQueue.build(items.iterator(), is_max=False)
    length = priority_queue.get_length() - 1
    priority_queue.dequeue()
    yield length
    yield priority_queue.get_length()
