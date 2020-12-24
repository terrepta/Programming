using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Jump : MonoBehaviour
{
    Rigidbody2D rb;
    public bool ReadyJump;
    public bool ReadyGround;
    public int ForceJump;
    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
    }

    void FixedUpdate()
    {
        if (ReadyJump && ReadyGround)
        {
            rb.AddForce(new Vector2(0, ForceJump));
            ReadyJump = false;
            ReadyGround = false;
        }
    }

    public void JumpPlayer()
    {
        ReadyJump = true;
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Ground")
        {
            ReadyGround = true;
        }

        else
        {
            ReadyGround = false;
        }
    }
}